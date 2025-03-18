#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define SCRIPT_VERSION "2.0 [ Build Settings Renderer Optimization ]"

// Fungsi untuk menampilkan notifikasi
void shell(const char *message) {
    char command[512];
    int len = snprintf(command, sizeof(command),
                       "cmd notification post -S bigtext -t '♨️ Sykaiviking ' 'Tag' '%s' > /dev/null 2>&1",
                       message);

    if (len < 0 || len >= sizeof(command)) {
        fprintf(stderr, "Error: Message too long for notification.\n");
        return;
    }

    if (system(command) != 0) {
        perror("Error executing notification command");
    }
}

// Fungsi untuk mengatur mode Vulkan dengan atau tanpa layers
void applySettings(int useLayers) {
    FILE *fp;
    char package[256];

    // Menjalankan perintah dan menangkap outputnya
    fp = popen("pm list package -3 | cut -f2 -d:", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return;
    }

    // Loop untuk membaca daftar paket aplikasi
    while (fgets(package, sizeof(package), fp) != NULL) {
        // Hapus karakter newline dari hasil fgets
        package[strcspn(package, "\n")] = 0;

        // Hindari memproses aplikasi "me.piebridge.brevent"
        if (strcmp(package, "me.piebridge.brevent") != 0) {
            char stopCmd[1520];

            // Terapkan skiavk
            system("setprop debug.hwui.renderer skiavk");
            system("setprop debug.renderengine.backend skiavk");
            system("setprop debug.vulkan.layer_path ''");
            system("setprop debug.vulkan.layers ''");
            system("setprop debug.performance.tuning 1");
            system("setprop debug.hwui.disable_vsync 1");
            system("setprop debug.vulkan.validation 1");
            system("setprop debug.sf.latch_unsignaled false");
            system("setprop debug.hwui.use_glsl_shaders 1");
            system("setprop debug.hwui.render_dirty_regions false");
            system("setprop debug.sf.hw 1");
            system("setprop debug.egl.hw 1");
            system("setprop debug.hwui.disable_vulkan 0");
            system("cmd activity kill-all");
            system("sync");

            // Hentikan aplikasi
            int len = snprintf(stopCmd, sizeof(stopCmd), "cmd activity force-stop %s", package);
            if (len > 0 && len < sizeof(stopCmd)) {
                system(stopCmd);
                printf("Processing %s\n", package);
            } else {
                fprintf(stderr, "Error: Command buffer overflow while stopping app %s\n", package);
            }
        }
    }

    // Tutup stream
    pclose(fp);

    // Menyusun perintah hanya jika mode Vulkan Layers aktif
    if (useLayers) {
        char commands[1520];
        int len = snprintf(commands, sizeof(commands),
                           "setprop debug.vulkan.layers VK_LAYER_LUNARG_swapchain "
                           "&& setprop debug.hwui.renderer vulkan "
                           "&& setprop debug.renderengine.backend vulkan "
                           "&& setprop debug.hwui.render_dirty_regions false "
                           "&& setprop debug.performance.tuning 1 "
                           "&& setprop debug.hwui.disable_vsync 1 "
                           "&& setprop debug.hwui.disable_vulkan 0 "
                           "&& setprop debug.vulkan.validation 1 "
                           "&& setprop debug.sf.latch_unsignaled false "
                           "&& setprop debug.hwui.use_glsl_shaders 1 "
                           "&& setprop debug.sf.hw 1 "
                           "&& setprop debug.egl.hw 1 "
                           "&& setprop debug.vulkan.layer_path /sdcard/Ques/vk "
                           "&& cmd activity kill-all "
                           "&& sync");

        if (len > 0 && len < sizeof(commands)) {
            if (system(commands) != 0) {
                fprintf(stderr, "Error: Failed to apply Vulkan settings.\n");
            }
        } else {
            fprintf(stderr, "Error: Command buffer overflow while setting Vulkan Layers\n");
        }
    }

    // Kirim notifikasi
    shell(useLayers ? "Success Apply Use Layers Sykaiviking"
                    : "Success Apply Without Layers Sykaiviking");
}

// Fungsi untuk menampilkan panduan penggunaan
void Usage() {
    printf("Sykaiviking %s - Vulkan Rendering Optimization Utility\n", SCRIPT_VERSION);
    printf("Usage: Sykaiviking [OPTION]\n\n");
    printf("Options:\n");
    printf("  -L           Enable Vulkan Layers mode (for enhanced rendering)\n");
    printf("  -N           Enable Without-Layers Vulkan mode (for stability)\n");
    printf("  -h, --help   Display this help message and exit\n\n");
    printf("Description:\n");
    printf("  Sykaiviking is a lightweight system optimization tool that dynamically\n");
    printf("  configures Vulkan rendering settings for improved performance and\n");
    printf("  responsiveness on Android devices.\n\n");
    printf("Examples:\n");
    printf("  Apply Vulkan Layers mode:\n");
    printf("      Sykaiviking -L\n\n");
    printf("  Apply Without-Layers Vulkan mode:\n");
    printf("      Sykaiviking -N\n\n");
    printf("System Requirements:\n");
    printf("  - Root access may be required for modifying system properties\n");
    printf("  - Compatible with devices running Vulkan-supported Android versions\n\n");
    printf("For more information, visit:\n");
    printf("  Vulkan API Documentation: https://developer.android.com/ndk/guides/graphics/getting-started\n");
    printf("  Android Debugging Guide:  https://developer.android.com/studio/command-line/adb\n\n");

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Usage();
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-L") == 0) {
            sleep(1);
            printf("- Applying Vulkan Use-Layers Mode\n");
            applySettings(1);
        } else if (strcmp(argv[i], "-N") == 0) {
            sleep(1);
            printf("- Applying Without-Layers Vulkan Mode\n");
            applySettings(0);
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            Usage();
        } else {
            printf("Unknown option: %s\n", argv[i]);
            Usage();
        }
    }

    sleep(1);
    printf("\n");
    printf(" ⚠️ Modul ini dilindungi hak cipta dan\n");
    printf(" hanya untuk penggunaan oleh pengguna biasa.\n");
    printf(" Setiap penggunaan kode, desain, atau fitur\n");
    printf(" oleh pengembang lain tanpa izin tertulis dari\n");
    printf(" pemilik hak cipta sangat dilarang.\n");
    printf("______________________________________________(+)\n\n");

    return 0;
}