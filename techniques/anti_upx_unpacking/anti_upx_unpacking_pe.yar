rule upx_antiunpack_pe {
     meta:
        description = "Anti-UPX Unpacking technique about section renaming and zero padding against upx reference structure"
        author = "hackeT"

    strings:
        $mz = "MZ"

        $upx0 = {55 50 58 30 00 00 00}  //section name UPX0
        $upx1 = {55 50 58 31 00 00 00}  //section name UPX1
        $upx_sig = "UPX!"               //UPX_MAGIC_LE32
        $upx_sig2 = {A1 D8 D0 D5}       //UPX_MAGIC2_LE32
        $zero = {00 00 00 00}

    condition:
        $mz at 0 and ( $upx_sig at 992 or $upx_sig2 at 992 )
        and 
        ( 
          not ($upx0 in (248..984) or $upx1 in (248..984)) // section renaming: 248 is the minimum offset after pe optional header.
        or 
          $zero in (992..1024)                             // zero padding against upx reference structure: pe header ends offset 1024.
        )
}
