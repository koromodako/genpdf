# GenPDF

## Usage

```bash
# display help
genpdf -h
# generate example document
genpdf example/QWebEngineView.mhtml example/QWebEngineView.pdf
```

## Dependencies

GenPDF uses Qt WebEngine for PDF creation so you need to setup Qt framework on your machine using Qt Online Installer.

Replace `y` and `z` in `6.y.z` with latest **minor** and **patch** numbers.

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

## Build

```bash
# run qmake
/path/to/Qt/6.y.z/gcc_64/bin/qmake
# run make
make
# test genpdf
./genpdf
```

## Test

```bash
# run test
./test
```

## Some alternatives

### wkhtmltopdf

:warning: As of January 2023, this project [is not maintained](https://wkhtmltopdf.org/status.html) :warning:

```bash
wkhtmltopdf --disable-javascript \
            example/wkhtmltopdf.html \
            example/wkhtmltopdf.pdf
```

### chromium

:warning: Javascript [cannot be disabled](https://stackoverflow.com/a/47538023) with this method :warning:

```bash
chromium --headless \
         --disable-gpu \
         --print-to-pdf=example/QWebEngineView.pdf \
         --no-pdf-header-footer \
         example/QWebEngineView.mhtml
```
