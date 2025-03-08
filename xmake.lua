add_rules("mode.debug", "mode.release")
add_requires("raylib")

target("database-lib")
	set_kind("static")
	add_files("database-lib/*.c")
	add_includedirs("database-lib/")

target("database-server")
	set_kind("binary")
	add_files("database-server/*.c")
	add_includedirs("database-server/", "extern/", "database-lib/")
	add_deps("database-lib")

target("database-gui")
	set_kind("binary")
	add_files("database-gui/*.c")
	add_includedirs("database-gui/", "extern/", "database-lib/")
	add_packages("raylib")
	add_deps("database-lib")


target("test")
	set_kind("binary")
	add_files("test/*.c")
	add_includedirs("test/", "extern/", "database-lib/")
	add_deps("database-lib")
