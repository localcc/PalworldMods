local projectName = "ReplicationEnabler"

target(projectName)
    set_kind("shared")
    set_languages("cxx23")
    set_exceptions("cxx")

    add_includedirs("include")
    add_headerfiles("include/**.hpp")

    add_files("src/**.cpp")

    add_deps("UE4SS")

    on_load(function (target)
        import("build_configs.build_configs", { rootdir = get_config("ue4ssRoot") })
        build_configs:set_output_dir(target)
    end)

    on_config(function (target)
        import("build_configs.build_configs", { rootdir = get_config("ue4ssRoot") })
        build_configs:config(target)
    end)

    after_clean(function (target)
        import("build_configs.build_configs", { rootdir = get_config("ue4ssRoot") })
        build_configs:clean_output_dir(target)
    end)