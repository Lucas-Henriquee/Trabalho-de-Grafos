#!/usr/bin/env bash
for var in "n100plap1i1.txt" "n100plap2i1.txt" "n100plap3i1.txt" "n100d03p1i2.txt" "n100d03p2i2.txt" "n100d03p3i2.txt" "n100d06p1i3.txt" "n100d06p2i3.txt" "n100d06p3i3.txt" "n200plap1i4.txt" "n200plap2i4.txt" "n200plap3i4.txt" "n200d03p1i5.txt" "n200d03p2i5.txt" "n200d03p3i5.txt" "n300plap1i1.txt" "n300plap2i4.txt" "n300plap3i5.txt" "n300d06p2i2.txt"
do
    for i in 0 1 2
    do
        echo "./execGrupoX ./instances_example/$var $i"
        ./execGrupoX "./instances_example/$var" "./saida.txt" "$i"
    done
done
