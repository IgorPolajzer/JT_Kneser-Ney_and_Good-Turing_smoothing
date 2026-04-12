# Jezikovne tehnologije - Jezikovni modeli z glajenjem Good-Turin in Kneser-Ney

## Rezultati

Modele sem zgradil na korpusu [kas-5000.text.txt](korpus/kas-5000.text.txt)

### Good Turing

- model zgrajen na 2-gramih
```text
C:\MAG\1_LETNIK\2_SEMESTER\JEZIKOVNE_TEHNOLOGIJE\RV2\cmake-build-debug\RV2.exe -p models/Good_Turing-2-gram-5000.txt
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