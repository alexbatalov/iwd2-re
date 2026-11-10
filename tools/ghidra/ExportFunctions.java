// Export every function to <out>/functions.json plus per-function decompiled C
// and disassembly at <out>/decomp/0xADDR.c and <out>/decomp/0xADDR.asm.
// Headless: -postScript ExportFunctions.java <out-dir> [--no-decomp]
// Output is derived from the copyrighted binary: keep it outside the repo.
// @category iwd2-re

import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;

public class ExportFunctions extends GhidraScript {
    private static String hex(Address a) {
        return String.format("0x%X", a.getOffset());
    }

    private static String json(String s) {
        StringBuilder b = new StringBuilder("\"");
        for (char c : s.toCharArray()) {
            switch (c) {
            case '"': b.append("\\\""); break;
            case '\\': b.append("\\\\"); break;
            case '\n': b.append("\\n"); break;
            default:
                if (c < 0x20) b.append(String.format("\\u%04x", (int)c));
                else b.append(c);
            }
        }
        return b.append('"').toString();
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Path out = Path.of(args.length > 0 ? args[0] : askDirectory("Output", "Export").getAbsolutePath());
        boolean decomp = !(args.length > 1 && args[1].equals("--no-decomp"));
        Path decompDir = out.resolve("decomp");
        Files.createDirectories(decompDir);

        DecompInterface ifc = null;
        if (decomp) {
            ifc = new DecompInterface();
            DecompileOptions opts = new DecompileOptions();
            ifc.setOptions(opts);
            ifc.toggleCCode(true);
            ifc.toggleSyntaxTree(false);
            ifc.openProgram(currentProgram);
        }

        List<String> entries = new ArrayList<>();
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        int n = 0;
        while (it.hasNext() && !monitor.isCancelled()) {
            Function f = it.next();
            if (f.isExternal()) continue;
            Address entry = f.getEntryPoint();
            String addr = hex(entry);

            Set<String> callers = new TreeSet<>();
            for (Function c : f.getCallingFunctions(monitor)) callers.add(hex(c.getEntryPoint()));
            Set<String> callees = new TreeSet<>();
            for (Function c : f.getCalledFunctions(monitor)) callees.add(hex(c.getEntryPoint()));

            long size = f.getBody().getNumAddresses();
            entries.add("{\"addr\":" + json(addr)
                + ",\"name\":" + json(f.getName(true))
                + ",\"size\":" + size
                + ",\"is_thunk\":" + f.isThunk()
                + ",\"signature\":" + json(f.getPrototypeString(false, false))
                + ",\"callers\":[" + String.join(",", callers.stream().map(ExportFunctions::json).toList()) + "]"
                + ",\"callees\":[" + String.join(",", callees.stream().map(ExportFunctions::json).toList()) + "]}");

            try (PrintWriter w = new PrintWriter(Files.newBufferedWriter(decompDir.resolve(addr + ".asm"), StandardCharsets.UTF_8))) {
                w.println("; " + f.getName(true) + " @ " + addr + " size " + size);
                InstructionIterator ii = currentProgram.getListing().getInstructions(f.getBody(), true);
                while (ii.hasNext()) {
                    Instruction ins = ii.next();
                    w.println(String.format("%08X  %s", ins.getAddress().getOffset(), ins.toString()));
                }
            }

            if (decomp) {
                DecompileResults r = ifc.decompileFunction(f, 120, monitor);
                String c = r.decompileCompleted() ? r.getDecompiledFunction().getC() : ("// decompile failed: " + r.getErrorMessage());
                Files.writeString(decompDir.resolve(addr + ".c"), "// " + f.getName(true) + " @ " + addr + "\n" + c, StandardCharsets.UTF_8);
            }
            if (++n % 500 == 0) println("exported " + n);
        }
        Files.writeString(out.resolve("functions.json"), "[\n" + String.join(",\n", entries) + "\n]\n", StandardCharsets.UTF_8);
        println("ExportFunctions: " + n + " functions -> " + out);
    }
}
