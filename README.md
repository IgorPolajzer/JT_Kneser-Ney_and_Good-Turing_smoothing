# Jezikovne tehnologije - Jezikovni modeli z glajenjem Good-Turin in Kneser-Ney

## Rezultati

Modele sem zgradil na korpusu [kas-5000.text.txt](korpus/kas-5000.text.txt)

### Good Turing

- model zgrajen na 2-gramih
```text
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -p models/Good_Turing-2-gram-5000.txt
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
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -mp models/Kneser-Ney-2-gram-5000.txt korpus/kas-6000.text.txt
Perplexity: 51.1449

Process finished with exit code 0
```

- model zgrajen na 3-gramih
```text
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -p models/Good_Turing-3-gram-5000.txt
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
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -mp models/Kneser-Ney-2-gram-5000.txt korpus/kas-6000.text.txt
Perplexity: 51.1449

Process finished with exit code 0
```

### Kneser-Ney
- model zgrajen na 2-gramih
```text
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -p models/Kneser-Ney-2-gram-5000.txt
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
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -mp models/Kneser-Ney-2-gram-5000.txt korpus/kas-6000.text.txt
Perplexity: 51.1449

Process finished with exit code 0
```

- model zgrajen na 3-gramih
```text
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -p models/Kneser-Ney-3-gram-5000.txt
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

```text
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -mp models/Kneser-Ney-3-gram-5000.txt korpus/kas-6000.text.txt
Perplexity: 5.58331741048027740959

Process finished with exit code 0
```