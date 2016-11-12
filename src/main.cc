
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

// ---------------------------------------------------------------------

// [[Rcpp::export]]
SEXP R_AddInternetPassword(const std::string& servername,
			   const std::string& account,
			   int port,
			   const std::string& password) {

  return Rcpp::wrap(keytar::AddInternetPassword(servername, account, port,
						password));
}

// [[Rcpp::export]]
SEXP R_GetInternetPassword(const std::string& servername,
			   const std::string& account,
			   int port) {

  std::string password;
  bool result = keytar::GetInternetPassword(servername, account, port,
					    &password);
  if (!result) stop("Cannot find password");
  return Rcpp::wrap(password);
}

// [[Rcpp::export]]
SEXP R_DeleteInternetPassword(const std::string& servername,
			      const std::string& account,
			      int port) {

  return Rcpp::wrap(keytar::DeleteInternetPassword(servername, account,
						   port));
}

// [[Rcpp::export]]
SEXP R_FindInternetPassword(const std::string& servername,
			    int port) {

  std::string password;
  bool result = keytar::FindInternetPassword(servername, port, &password);
  if (!result) stop("Cannot find password");
  return Rcpp::wrap(password);
}
