# GenPDF

## Build on Linux

### Dependencies for Qt 6.8.2

Setup Qt framework on your machine using Qt Online Installer.

Select the following components only :

- Extensions
  - Qt WebEngine
    - Qt 6.8.2
      - Desktop
- Qt
  - Qt 6.8.2
    - Desktop
    - Additional Libraries
      - Qt Positioning
      - Qt WebChannel
      - Qt WebView

### Configure and make

```bash
# run qmake
/path/to/Qt/6.8.2/gcc_64/bin/qmake
# run make
make
# test genpdf
./genpdf
```
