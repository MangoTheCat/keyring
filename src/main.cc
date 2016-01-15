
#include <Rcpp.h>
using namespace Rcpp;

#include "keytar.h"

// [[Rcpp::export]]
SEXP R_AddPassword(const std::string& service,
		   const std::string& account,
		   const std::string& password) {

  return Rcpp::wrap(keytar::AddPassword(service, account, password));
}

// [[Rcpp::export]]
SEXP R_GetPassword(const std::string& service,
		   const std::string& account) {
  std::string password;
  bool result = keytar::GetPassword(service, account, &password);
  if (!result) stop("Cannot find password");
  return Rcpp::wrap(password);
}


// [[Rcpp::export]]
SEXP R_DeletePassword(const std::string& service,
		      const std::string& account) {

  return Rcpp::wrap(keytar::DeletePassword(service, account));
}

// [[Rcpp::export]]
SEXP R_FindPassword(const std::string& service) {

  std::string password;
  bool result = keytar::FindPassword(service, &password);
  if (!result) stop("Cannot find password");
  return Rcpp::wrap(password);
}
