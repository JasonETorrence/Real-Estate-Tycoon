cmake_minimum_required(VERSION 3.15)
project(Real_Estate_Tycoon)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Real_Estate_Tycoon
        main.cpp
        Player/Player.cpp
        Player/Player.h
        Property/Property.h
        Tenant/Tenant.h
        Tenant/Tenant.cpp
        Property/Property.cpp
        Utilities/Utilities.cpp
        Utilities/Utilities.h
        Property/House/House.cpp
        Property/House/House.h
        Property/BusinessComplex/BusinessComplex.cpp
        Property/BusinessComplex/BusinessComplex.h
        Property/ApartmentComplex/ApartmentComplex.cpp
        Property/ApartmentComplex/ApartmentComplex.h
        Tenant/Civilian/Civilian.cpp
        Tenant/Civilian/Civilian.h
        Tenant/Business/Business.cpp
        Tenant/Business/Business.h
        Driver.cpp
        Driver.h Utilities/TotallyNotAVector.h )