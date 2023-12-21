//
// Created by andrey on 30.11.23.
//

#ifndef USERVERAPP_JWT_HPP
#define USERVERAPP_JWT_HPP
#include <string>

#include <jwt/jwt.hpp>

namespace userverApp::utils::jwt {

std::string GenerateJWT(std::string_view id);
::jwt::jwt_payload DecodeJWT(std::string_view jwt_token);

}  // namespace userverApp::utils::jwt
#endif  // USERVERAPP_JWT_HPP
