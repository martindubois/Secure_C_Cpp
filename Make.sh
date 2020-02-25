#!/bin/sh

# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Make.sh

echo Executing  Make.sh  ...

# ===== Execution ===========================================================

cd BaseLib
    make
    if [ 0 != $? ];
    then
        echo ERROR  BaseLib - make  failed
        exit 10
    fi
cd ..

for i in BO_Dynamic BO_Global BO_Local \
         DynamicMemory                 \
         Format_0 Format_0_Safe        \
         Integer_AddSub Integer_Size   \
         Random_0                      \
         Scan_0 Scan_0_Safe            \
         Scan_0_a Scan_0_a_Safe        \
         Signal                        \
         String String_Safe            \
         String_0 String_0_Safe        \
         String_STL                    \
         SymLink_a                     \
         TCP_Hacker_0 TCP_Server_0     \
         UDP_Hacker_0 UDP_Server_0 UDP_Server_0_a
do
    cd $i
    make
    if [ 0 != $? ];
    then
        echo ERROR  $i - make  failed
        exit 20
    fi
    cd ..
done

# ===== End =================================================================

echo OK
