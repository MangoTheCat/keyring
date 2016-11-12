
is_string <- function(x) {
  is.character(x) && length(x) == 1 && !is.na(x)
}

is_count <- function(x) {
  is.numeric(x) && length(x) == 1 && !is.na(x) && as.integer(x) == x
}
