# Jezikovne tehnologije - Jezikovni modeli z glajenjem Good-Turin in Kneser-Ney

## Rezultati

Modele sem zgradil na korpusu [kas-5000.text.txt](korpus/kas-5000.text.txt)

### Good Turing

- model zgrajen na 2-gramih
```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -p model/gt_2.txt korpus/kas-6000.text.txt
Input sentence: Univerza v Mariboru
Vhod: Univerza v Mariboru
Vmesni rezultati: 
Fakulteta
za
to
je
bila
Izhod: Univerza v Mariboru Fakulteta za to je bila

Process finished with exit code 0
```

Perpleksnost:

```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -mp model/gt_2.txt korpus/kas-6000.text.txt
Perplexity: 3.67432138611853531529

Process finished with exit code 0
```

- model zgrajen na 3-gramih
```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -p model/gt_3.txt korpus/kas-6000.text.txt
Input sentence: Univerza v Mariboru
Vhod: Univerza v Mariboru
Vmesni rezultati: 
Fakulteta
za
varnostne
vede
smer
Izhod: Univerza v Mariboru Fakulteta za varnostne vede smer

Process finished with exit code 0
```

Perpleksnost:

```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -mp model/gt_3.txt korpus/kas-6000.text.txt
Perplexity: 1.24712297316746800746

Process finished with exit code 0
```

### Kneser-Ney
- model zgrajen na 2-gramih
```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -p model/kn_2.txt korpus/kas-6000.text.txt
Input sentence: Univerza v Mariboru
Vhod: Univerza v Mariboru
Vmesni rezultati: 
in
se
je
bila
Natascha
Izhod: Univerza v Mariboru in se je bila Natascha

Process finished with exit code 0
```

Perpleksnost: 

```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -mp model/kn_2.txt korpus/kas-6000.text.txt
Perplexity: 51.14493501445728185217

Process finished with exit code 0
```

- model zgrajen na 3-gramih
```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -p model/kn_3.txt korpus/kas-6000.text.txt
Input sentence: Univerza v Mariboru
Vhod: Univerza v Mariboru
Vmesni rezultati: 
Fakulteta
za
varnostne
vede
</s>
Izhod: Univerza v Mariboru Fakulteta za varnostne vede </s>

Process finished with exit code 0
```

```text
/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/JEZIKOVNE_TEHNOLOGIJE/JT_RV2/cmake-build-debug/RV2 -mp model/kn_3.txt korpus/kas-6000.text.txt
Perplexity: 5.58331741048027740959

Process finished with exit code 0
```