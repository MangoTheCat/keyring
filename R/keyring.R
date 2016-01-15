
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
