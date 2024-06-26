#include "stream.h"
#include "compression.h"

#include <src/library/testing/unittest/registar.h>
#include <src/library/testing/unittest/tests_data.h>

#include <src/util/stream/zlib.h>
#include <unordered_set>

Y_UNIT_TEST_SUITE(THttpCompressionTest) {
    static const std::string DATA = "I'm a teapot";

    Y_UNIT_TEST(TestGetBestCodecs) {
        UNIT_ASSERT(TCompressionCodecFactory::Instance().GetBestCodecs().size() > 0);
    }

    Y_UNIT_TEST(TestEncoder) {
        std::stringStream buffer;

        {
            auto encoder = TCompressionCodecFactory::Instance().FindEncoder("gzip");
            UNIT_ASSERT(encoder);

            auto encodedStream = (*encoder)(&buffer);
            encodedStream->Write(DATA);
        }

        TZLibDecompress decompressor(&buffer);
        UNIT_ASSERT_EQUAL(decompressor.ReadAll(), DATA);
    }

    Y_UNIT_TEST(TestDecoder) {
        std::stringStream buffer;

        {
            TZLibCompress compressor(TZLibCompress::TParams(&buffer).SetType(ZLib::GZip));
            compressor.Write(DATA);
        }

        auto decoder = TCompressionCodecFactory::Instance().FindDecoder("gzip");
        UNIT_ASSERT(decoder);

        auto decodedStream = (*decoder)(&buffer);
        UNIT_ASSERT_EQUAL(decodedStream->ReadAll(), DATA);
    }

    Y_UNIT_TEST(TestChooseBestCompressionScheme) {
        std::unordered_set<std::string> accepted;

        auto checkAccepted = [&accepted](const std::string& v) {
            return accepted.contains(v);
        };

        UNIT_ASSERT_VALUES_EQUAL("identity", NHttp::ChooseBestCompressionScheme(checkAccepted, {"gzip", "deflate"}));
        accepted.insert("deflate");
        UNIT_ASSERT_VALUES_EQUAL("deflate", NHttp::ChooseBestCompressionScheme(checkAccepted, {"gzip", "deflate"}));
        accepted.insert("*");
        UNIT_ASSERT_VALUES_EQUAL("gzip", NHttp::ChooseBestCompressionScheme(checkAccepted, {"gzip", "deflate"}));
    }
} // THttpCompressionTest suite
