#! /usr/bin/sh

LANG=C
export LANG

if [ $# -ne 3 ] || [ ! -f $1 ]
then
    print -u2 "Recipe file name or Key is wrong."
    exit -1
fi

key1_val="$2"
key2_val="$3"

/usr/bin/awk -v key1="$key1_val" -v key2="$key2_val" '
BEGIN {
    matched_count = 0
    is_header     = 0

    key1_col = 2                         # column 2 for search key fields
    key2_col = 3                         # column 3 for search key fields
    max_col = 32

    fs = "\t"                           # field separator for the file
    cr = "\n"

    spc_lbl_len = 0
    spc_lbl[++spc_lbl_len] = "TCO"
    spc_lbl[++spc_lbl_len] = "Limit File"
    spc_lbl[++spc_lbl_len] = "DIE Label"
    spc_lbl[++spc_lbl_len] = "DIE Type"
    spc_lbl[++spc_lbl_len] = "MOD Label"

    for (j = 1; j <= spc_lbl_len; j++) {
        lbl[j] = ""
    }
}


function lbl2col(l, k_type)             # File label to column number
{
    for (i = 1; i <= max_col; i++) {
        if (match(l[i], "^"k_type"$")) {
            return i
        }
    }
    return -1;
}

/^[^#]/ {                               # process for each recipe line
    ln = $0
    split(ln, itm, fs)
    if (match(itm[key1_col], "^"key1"$")) {

        if (match(itm[key2_col], "^"key2"$")) {

            gsub(fs, cr, ln)                # tab => cr replacement
            print ln                        # print matched line

            for (j = 1; j <= spc_lbl_len; j++) {
                print "#",spc_lbl[j]        # print Spec label
                col = lbl2col(lbl, spc_lbl[j]);
                gsub("^ *", "", itm[col])   # trim out space
                gsub(" *$", "", itm[col])   # trim out space
                gsub(" *, *", cr, itm[col]) # comma separated => separated lines
                print itm[col]              # print matched Spec names
            }
            print "#","EOD"                 # end of recipe data

            matched_count++
        }

    }
}

/^#/ {                                  # search spec label position
    if (is_header == 0) {
        sub(/^#/, "")

        split($0, tmp_lbl, fs)

        lbl_count = 0
        for (i = 1; i <= max_col; i++) {
            for (j = 1; j <= spc_lbl_len; j++) {
                if (match(tmp_lbl[i], spc_lbl[j])) {
                    lbl_count++
                }
            }
        }
        if (lbl_count >= spc_lbl_len) { # label line if there are required labels

            split($0, lbl, fs)

            is_header = 1
        }
    }
}

END {                                   # check error
    if (matched_count == 0) {
        exit -1
    }
    if (matched_count > 1) {
        exit 1
    }

    exit 0
}
' $1

retval=$?
if [ $retval -eq 1 ]
then
    print -u2 "More than two recipes are found by the key, \"$key1_val\"."
    print -u2 "                                            \"$key2_val\"."
    exit 1
elif [ $retval -ne 0 ]
then
    print -u2 "No recipe is found by the key, \"$key1_val\"."
    print -u2 "                               \"$key2_val\"."
    exit -1
fi

exit 0
