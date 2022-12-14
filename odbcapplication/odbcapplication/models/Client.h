#ifndef CLIENT_H
#define CLIENT_H

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include "ActiveRecord.h"

using namespace std;

class Client : public ActiveRecord {

private:
	int insert(HDBC hDBC) override;
	bool update(HDBC hDBC) override;

public:
	string companyName, postalAddress, phoneNumber, faxNumber, email;

	Client();
	Client(long long id);
	Client(long long id, string companyName, string postalAddress, string phoneNumber, string faxNumber, string email);

	bool remove(HDBC hDBC) override;
	Client load(HDBC hDBC);

	friend bool operator==(const Client& lhs, const Client& rhs) {
		return lhs.id == rhs.id 
			&& lhs.companyName == rhs.companyName 
			&& lhs.postalAddress == rhs.postalAddress
			&& lhs.phoneNumber == rhs.phoneNumber
			&& lhs.faxNumber == rhs.faxNumber
			&& lhs.email == rhs.email;
	}

	std::string toString() {
		char s[512];
		sprintf_s(s, 512, "Company Name: %s, Postal Address: %s, Phone Number: %s, Fax Number: %s, Email: %s", companyName.c_str(), postalAddress.c_str(), phoneNumber.c_str(), faxNumber.c_str(), email.c_str());
		return string(s);
	}

	std::string toStringCN() {
		char s[200];
		sprintf_s(s, 200, "Company Name: %s", companyName.c_str());
		return string(s);
	}
};

#endif