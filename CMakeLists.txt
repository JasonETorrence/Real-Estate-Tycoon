cmake_minimum_required(VERSION 3.15)
project(Real_Estate_Tycoon)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Real_Estate_Tycoon
        main.cpp
        Player/Player.cpp
        Player/Player.h
        Property/Property.cpp
        Property/Property.h
        Tenant/Tenant.cpp
        Tenant/Tenant.h
        Utilities/Utilities.cpp
        Utilities/Utilities.h Property/House/House.cpp Property/House/House.h "Property/Business Complex/BusinessComplex.cpp" "Property/Business Complex/BusinessComplex.h" "Property/Apartment Complex/ApartmentComplex.cpp" "Property/Apartment Complex/ApartmentComplex.h" Tenant/Civilian/Civilian.cpp Tenant/Civilian/Civilian.h Tenant/Business/Business.cpp Tenant/Business/Business.h)