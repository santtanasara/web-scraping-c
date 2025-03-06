#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

// Callback para gravar os dados recebidos
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE *arquivo = (FILE *)userdata;
    return fwrite(ptr, size, nmemb, arquivo); // Salva os dados no arquivo
}

int main() {
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if (curl) {
        FILE *file = fopen("pagina.html", "wb"); // Abre um arquivo para salvar o HTML
        if (!file) {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro ao fazer a requisição: %s\\n", curl_easy_strerror(res));
        }
        
        fclose(file);
        curl_easy_cleanup(curl);
    }
    
    return 0;
}
