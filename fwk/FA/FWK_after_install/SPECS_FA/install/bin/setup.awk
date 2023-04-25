BEGIN {
    num = 10
    flg = 0
}
/ ! SHL_SEARCH \/opt\/SPECS_FA\/dmh\/lib/{
    flg = 1
}
/ ! SHL_LOAD libtcl8.4.so/{
    flg = 1
}
/ ! SHL_LOAD libm.so/{
    flg = 1
}
/Specify a shared library to be loaded at boot/{
    printf "%4d  ! SHL_SEARCH /opt/SPECS_FA/dmh/lib\n",num
    num = num + 10
}
/Specify whether to keep all shared libraries permanently/{
    printf "%4d  ! SHL_LOAD libtcl8.4.so\n",num
    num = num + 10
    printf "%4d  ! SHL_LOAD libm.so\n",num
    num = num + 10
} 
/^[0-9]+/{
    if(flg == 0 ){
        sub($1,num,$0)
        print $0
        num = num + 10
    }
    flg =0
} 
!/^[0-9]+/{
    print $0
}
