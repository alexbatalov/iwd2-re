#include "test.h"

#include "CResRef.h"

TEST_CASE("CResRef stores up to 8 chars, upper-cased")
{
    CResRef ref("ar1000");
    CString s;
    ref.CopyToString(s);
    CHECK(s == "AR1000");
    CHECK(ref.IsValid());
    CHECK(ref == "AR1000");
    CHECK(ref == "ar1000");
}

TEST_CASE("CResRef truncates names longer than 8 chars")
{
    CResRef ref("ABCDEFGHIJ");
    CString s;
    ref.CopyToString(s);
    CHECK(s.GetLength() <= 8);
    CHECK(s == "ABCDEFGH");
}

TEST_CASE("default CResRef is invalid")
{
    CResRef ref;
    CHECK_FALSE(ref.IsValid());
    CHECK(!ref);
}
