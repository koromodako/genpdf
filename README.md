# GenPDF

## Build on Linux

### Dependencies for Qt 6.y.z

Setup Qt framework on your machine using Qt Online Installer.

Replace `y` and `z` in `6.y.z` with appropriate **minor** and **patch** numbers.

Select the following components only :

- Extensions
  - Qt WebEngine
    - Qt 6.y.z
      - Desktop
- Qt
  - Qt 6.y.z
    - Desktop
    - Additional Libraries
      - Qt Positioning
      - Qt WebChannel
      - Qt WebView


### Configure and make

```bash
# run qmake
/path/to/Qt/6.y.z/gcc_64/bin/qmake
# run make
make
# test genpdf
./genpdf
```


### Run test

```bash
# run test
./test
```
