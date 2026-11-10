// Apply function names from a "0xADDR Name" text file (function_names.db) and
// make sure a function exists at every listed address.
// Headless: -postScript ApplyNames.java <path-to-function_names.db>
// @category iwd2-re

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class ApplyNames extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Path path = Path.of(args.length > 0 ? args[0] : askFile("function_names.db", "Apply").getAbsolutePath());
        List<String> lines = Files.readAllLines(path);
        int created = 0, renamed = 0, failed = 0;
        for (String line : lines) {
            String[] parts = line.trim().split("\\s+", 2);
            if (parts.length != 2 || !parts[0].startsWith("0x")) {
                continue;
            }
            String name = parts[1];
            if (name.startsWith("Unwind@")) {
                continue;
            }
            Address addr = toAddr(Long.parseLong(parts[0].substring(2), 16));
            Function f = getFunctionAt(addr);
            if (f == null) {
                disassemble(addr);
                CreateFunctionCmd cmd = new CreateFunctionCmd(addr);
                if (cmd.applyTo(currentProgram, monitor)) {
                    f = getFunctionAt(addr);
                    created++;
                } else {
                    failed++;
                    continue;
                }
            }
            if (name.startsWith("FUN_") || name.isEmpty()) {
                continue;
            }
            try {
                f.setName(name.replace(' ', '_'), SourceType.IMPORTED);
                renamed++;
            } catch (Exception e) {
                failed++;
            }
        }
        println("ApplyNames: created=" + created + " renamed=" + renamed + " failed=" + failed);
    }
}
