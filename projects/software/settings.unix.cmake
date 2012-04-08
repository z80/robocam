
set( CROSS True CACHE TYPE BOOL )

set( ICE_LIB_PATH "../openwrt/build/icee/cppe/lib" )
set( ICEE_PATH "../../openwrt/build/icee/cppe/include" )
set( ICEE_UTIL_PATH "../../openwrt/build/icee/cpp/include" )
if ( CROSS )
    set( ICE_LIB_PATH_EMB "../openwrt/build/emb/cppe/lib" )
    set( ICEE_PATH_EMB "../../openwrt/build/emb/cppe/include" )
    set( ICEE_UTIL_PATH_EMB "../../openwrt/build/emb/cpp/include" )
    set( OPENWRT_PATH /home/z80/projects/openwrt/OpenWrt-Toolchain-brcm47xx-for-mipsel-gcc-4.3.3+cs_uClibc-0.9.30.1/toolchain-mipsel_gcc-4.3.3+cs_uClibc-0.9.30.1 CACHE TYPE PATH )
    set( LIB_PATH_EMB /home/z80/projects/openwrt/proj/build_dir/target-mipsel_uClibc-0.9.30.1/OpenWrt-SDK-brcm47xx-for-Linux-i686-gcc-4.3.3+cs_uClibc-0.9.30.1/staging_dir/target-mipsel_uClibc-0.9.30.1/usr/lib )
    set( INC_PATH_EMB /home/z80/projects/openwrt/proj/build_dir/target-mipsel_uClibc-0.9.30.1/OpenWrt-SDK-brcm47xx-for-Linux-i686-gcc-4.3.3+cs_uClibc-0.9.30.1/staging_dir/target-mipsel_uClibc-0.9.30.1/usr/include )
endif ( CROSS )

