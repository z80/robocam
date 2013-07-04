
if ( WIN32 )
    set( VPX_INCLUDE_DIRS "${ROOT}/3dparty/vpx/include" 
                          "${ROOT}/3dparty/vpx/include/vpx" 
                          "${ROOT}/3dparty/vpx/config" )
    set( VPX_LIBRARIES    optimized ${ROOT}/3dparty/vpx/lib/release/vpxmtd.lib 
                          debug     ${ROOT}/3dparty/vpx/lib/debug/vpxmtd.lib 
                          optimized ${ROOT}/3dparty/vpx/lib/release/gtestmtd.lib 
                          debug     ${ROOT}/3dparty/vpx/lib/debug/gtestmtd.lib )
endif ( WIN32 )





