#include "defs.hpp"
#include "ScriptEnvironment.hpp"


int l61_extension_init(l61_api_extension_t* api)
{
    std::println("ver: {}", api->l61Ctx.version);
    api->scriptCtx->addValue("bash"s, "fuck");
    return 0;
}

C_CALL int __l61_rt_ex_init__(l61_api_extension_t* api) // NOLINT(*-reserved-identifier)
{
    return l61_extension_init(api);
}