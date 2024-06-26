#pragma once

#include <ydb-cpp-sdk/util/generic/ptr.h>

namespace NUnitTest {
    // Plugins are deprecated, please use Y_TEST_HOOK_* from src/library/hook/hook.h
    namespace NPlugin {
        class IPlugin {
        public:
            virtual ~IPlugin() {
            }

            virtual void OnStartMain(int /*argc*/, char* /*argv*/ []) {
            }

            virtual void OnStopMain(int /*argc*/, char* /*argv*/ []) {
            }
        };

        void OnStartMain(int argc, char* argv[]);
        void OnStopMain(int argc, char* argv[]);

        class TPluginRegistrator {
        public:
            TPluginRegistrator(TSimpleSharedPtr<IPlugin> plugin);
        };

    }
}
