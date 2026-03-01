#include <windows.h>
#include <stdio.h>
#include <intrin.h>

int is_vm() {
    int cpuInfo[4];
    
    // Step 1: Check the official Hypervisor Present Bit (Leaf 1, ECX bit 31)
    __cpuid(cpuInfo, 1);
    if (!(cpuInfo[2] & (1 << 31))) {
        return 0; // Bit not set = likely physical hardware
    }

    // Step 2: Since a hypervisor is present, check the brand
    __cpuid(cpuInfo, 0x40000000);
    
    // Example: Detect VMware
    // EBX: 0x61774d56 ("VMwa"), ECX: 0x4d566572 ("reVM"), EDX: 0x65726177 ("ware")
    if (cpuInfo[1] == 0x61774d56) return 1; 
    
    // Example: Detect VirtualBox
    if (cpuInfo[1] == 0x786f4256) return 1; // "VBox"
    
    return 0; 
}

void secret_logic(int input) {
    // Logic: ((input + 0x5) ^ 0x10) << 2
    int transform = ((input + 5) ^ 16) << 2;

    if (transform == 500) {
        printf("\nACCESS GRANTED\n");
    } else {
        printf("\nAccess Denied\n");
    }
}

int main() {
    int user_key;

    if (IsDebuggerPresent()) {
        printf("Debugger found! Exiting for security\n");

        Sleep(2000);
        return 1;
    }

    if (is_vm()) {
        printf("VM Detected! I only run on real hardware.\n");

        Sleep(2000);
        return 1;
    }

    printf("--- THE MEGA VAULT ---\n");
    printf("Enter the secret Key: ");
    scanf("%d", &user_key);

    secret_logic(user_key);

    printf("Press Enter to close...");
    getchar(); getchar();
    return 0;
}