--[[%
%if !check_feature(standard_set)
    %error("This preprocessor Does not have standard feature set")
%else
    %policy(enable, v1_pp_features)
    %policy(enable, v1_pp_predefines)
    %policy(enable, strong_type_macro_func_sig)
    %import("ext_math.defs.lpp61")
%end
]]

function test()
--%ifndef TEST_STR
--%   define TEST_STR "test"
--%end
--If you use a '%' at the beginning of comment Make it '%%'
    return --[[%{TEST_STR}]]
end


function optimized_runtime_call()
--[[%
%pp_func pp_time_math(num: @integer): @integer
    %val %{ty} %set 2
    %return (%{num} / %{ext_math_fancy_num}) ^ %{ty}
%end
]]
-- All code inside of a pre-processor function Example math will be performed at preprocessor time
    return --[[%pp_time_math(44)]]
end