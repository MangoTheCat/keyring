
#' @useDynLib keyring
NULL

#' @export

add_password <- function(service, account, password) {
  stopifnot(
    is_string(service),
    is_string(account),
    is_string(password)
  )

  R_AddPassword(service, account, password)
}

#' @export

get_password <- function(service, account) {
  stopifnot(
    is_string(service),
    is_string(account)
  )

  R_GetPassword(service, account)
}

#' @export

delete_password <- function(service, account) {
  stopifnot(
    is_string(service),
    is_string(account)
  )

  R_DeletePassword(service, account)
}

#' @export

find_password <- function(service) {
  stopifnot(
    is_string(service)
  )

  R_FindPassword(service)
}

## -------------------------------------------------------------------

#' @export

add_internet_password <- function(servername, account, password, port = 0) {
  stopifnot(
    is_string(servername),
    is_string(account),
    is_string(password),
    is_count(port)
  )

  R_AddInternetPassword(servername, account, port, password)
}

#' @export

get_internet_password <- function(servername, account, port = 0) {
  stopifnot(
    is_string(servername),
    is_string(account),
    is_count(port)
  )

  R_GetInternetPassword(servername, account, port)
}

#' @export

delete_internet_password <- function(servername, account, port = 0) {
  stopifnot(
    is_string(service),
    is_string(account),
    is_count(port)
  )

  R_DeleteInternetPassword(servername, account, port)
}

#' @export

find_internet_password <- function(servername, port = 0) {
  stopifnot(
    is_string(servername),
    is_count(port)
  )

  R_FindInternetPassword(servername, port)
}
