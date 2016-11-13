
#ifdef _WIN32

#include "keytar.h"

#include <windows.h>
#include <wincred.h>

namespace keytar {

bool AddPassword(const std::string& service,
                 const std::string& account,
                 const std::string& password) {
  std::string target_name = service + '/' + account;

  CREDENTIAL cred = { 0 };
  cred.Type = CRED_TYPE_GENERIC;
  cred.TargetName = const_cast<char*>(target_name.c_str());
  cred.CredentialBlobSize = password.size();
  cred.CredentialBlob = (LPBYTE)(password.data());
  cred.Persist = CRED_PERSIST_LOCAL_MACHINE;

  return ::CredWrite(&cred, 0) == TRUE;
}

bool GetPassword(const std::string& service,
                 const std::string& account,
                 std::string* password) {
  std::string target_name = service + '/' + account;

  CREDENTIAL* cred;
  if (::CredRead(target_name.c_str(), CRED_TYPE_GENERIC, 0, &cred) == FALSE)
    return false;

  *password = std::string(reinterpret_cast<char*>(cred->CredentialBlob),
                          cred->CredentialBlobSize);
  ::CredFree(cred);
  return true;
}

bool DeletePassword(const std::string& service, const std::string& account) {
  std::string target_name = service + '/' + account;

  return ::CredDelete(target_name.c_str(), CRED_TYPE_GENERIC, 0) == TRUE;
}

bool FindPassword(const std::string& service, std::string* password) {
  std::string filter = service + "*";

  DWORD count;
  CREDENTIAL** creds;
  if (::CredEnumerate(filter.c_str(), 0, &count, &creds) == FALSE)
    return false;

  *password = std::string(reinterpret_cast<char*>(creds[0]->CredentialBlob),
                          creds[0]->CredentialBlobSize);
  ::CredFree(creds);
  return true;
}

bool AddInternetPassword(const std::string& servername,
			 const std::string& account,
			 int port, // TODO: ignored
			 const std::string& password) {

  CREDENTIAL cred = { 0 };
  cred.Type = CRED_TYPE_GENERIC;
  cred.TargetName = const_cast<char*>(servername.c_str());
  cred.CredentialBlobSize = password.size();
  cred.CredentialBlob = (LPBYTE)(password.data());
  cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
  cred.UserName = const_cast<char*>(account.c_str());

  return ::CredWrite(&cred, 0) == TRUE;
}

bool GetInternetPassword(const std::string& servername,
			 const std::string& account,
			 int port,
			 std::string* password) {

  CREDENTIAL* cred;
  if (::CredRead(servername.c_str(), CRED_TYPE_GENERIC, 0, &cred) == FALSE)
    return false;

  *password = std::string(reinterpret_cast<char*>(cred->CredentialBlob),
                          cred->CredentialBlobSize);
  ::CredFree(cred);
  return true;
}

bool DeleteInternetPassword(const std::string& servername,
			    const std::string& account,
			    int port) {
  return ::CredDelete(servername.c_str(), CRED_TYPE_GENERIC, 0) == TRUE;
}

bool FindInternetPassword(const std::string& servername,
			  int port,
			  std::string* password) {

  std::string filter = servername + "*";

  DWORD count;
  CREDENTIAL** creds;
  if (::CredEnumerate(filter.c_str(), 0, &count, &creds) == FALSE)
    return false;

  *password = std::string(reinterpret_cast<char*>(creds[0]->CredentialBlob),
                          creds[0]->CredentialBlobSize);
  ::CredFree(creds);
  return true;
}

}  // namespace keytar

#endif
