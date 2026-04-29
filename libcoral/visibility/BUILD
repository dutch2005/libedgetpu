package(default_visibility = ["//visibility:public"])

config_setting(
    name = "public",
    values = {"define": "public=true"},
)

# Also add a filegroup or library just in case some things expect a target named 'public'
filegroup(
    name = "public_target",
    visibility = ["//visibility:public"],
)
