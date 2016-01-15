
# keyring

> Access the System Keyring from R

[![Linux Build Status](https://travis-ci.org/gaborcsardi/keyring.svg?branch=master)](https://travis-ci.org/gaborcsardi/keyring)

[![Windows Build status](https://ci.appveyor.com/api/projects/status/github/gaborcsardi/keyring?svg=true)](https://ci.appveyor.com/project/gaborcsardi/keyring)
[![](http://www.r-pkg.org/badges/version/keyring)](http://www.r-pkg.org/pkg/keyring)
[![CRAN RStudio mirror downloads](http://cranlogs.r-pkg.org/badges/keyring)](http://www.r-pkg.org/pkg/keyring)


Modern OSes store passwords, and other confidential information in a keyring with a master password. This package allows access to the keyring of the OS from R. It supports Windows, Mac OS X and Linux systems.

## Installation

```r
devtools::install_github("gaborcsardi/keyring")
```

## Usage

```r
library(keyring)
```

## License

MIT + file LICENSE © [Gabor Csardi](https://github.com/gaborcsardi).
