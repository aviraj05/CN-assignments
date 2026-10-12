#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cout << "SUBNETTING" << endl;
    cout << "Subnetting is the process of splitting a large network into smaller, logical parts called subnets. It helps save IP addresses, speeds up network traffic, and keeps data safe." << endl;
   
    cout << endl;
   
    cout << "SUBNET MASK" << endl;
    cout << "a 32-bit number that splits an IP address into two parts: the network portion and the host portion. It helps devices figure out if another computer is on the same local network or on a different one." << endl;
   
    int a, b, c, d;
    char dot1, dot2, dot3;
   
    cout << endl;
    cout << "Enter IP Address: ";
    cin >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d;

    if (a >= 1 && a <= 126)
    {
        cout << "\nClass : A" << endl;
        cout << "Default Subnet Mask : 255.0.0.0 (/8)" << endl;
        cout << "Number of Networks : 126" << endl;
        cout << "Hosts per Network : 16,777,214" << endl;
    }
    else if (a == 127)
    {
        cout << "\nLoopback Address" << endl;
        cout << "Address : 127.0.0.1" << endl;
        cout << "Used for testing the local machine." << endl;
    }
    else if (a >= 128 && a <= 191)
    {
        cout << "\nClass : B" << endl;
        cout << "Default Subnet Mask : 255.255.0.0 (/16)" << endl;
        cout << "Number of Networks : 16,384" << endl;
        cout << "Hosts per Network : 65,534" << endl;
    }
    else if (a >= 192 && a <= 223)
    {
        cout << "\nClass : C" << endl;
        cout << "Default Subnet Mask : 255.255.255.0 (/24)" << endl;
        cout << "Number of Networks : 2,097,152" << endl;
        cout << "Hosts per Network : 254" << endl;
    }
    else if (a >= 224 && a <= 239)
    {
        cout << "\nClass : D" << endl;
        cout << "Purpose : Multicast" << endl;
        cout << "Subnet Mask : Not Applicable" << endl;
    }
    else if (a >= 240 && a <= 255)
    {
        cout << "\nClass : E" << endl;
        cout << "Purpose : Experimental / Research" << endl;
        cout << "Subnet Mask : Not Applicable" << endl;
    }
    else
    {
        cout << "\nInvalid IP Address!" << endl;
    }
    int hostBits;

    if(a >= 1 && a <= 126)
    {
    hostBits = 24;
    }
    else if(a >= 128 && a <= 191)
    {
    hostBits = 16;
    }
    else if(a >= 192 && a <= 223)
    {
    hostBits = 8;
    }
    long long hosts = pow(2, hostBits) - 2;
    cout << "Formula for hosts per Network : " << "2^"<<hostBits<<"-2" << endl;


    return 0;
}