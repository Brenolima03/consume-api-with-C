#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define URL_MAX_LENGTH 150
#define PAYLOAD_MAX_LENGTH 200
#define ID_MAX_LENGTH 50
#define LINE_MAX_LENGTH 200

// Function to perform a POST request.
void post(const char *url, const char *data) {
  // Initialize a CURL session handle.
  CURL *curl = curl_easy_init();

  if (curl) {
    CURLcode res;
    char post_url[URL_MAX_LENGTH];
    snprintf(post_url, sizeof(post_url), "%s%s", url, "post/");

    // Set the URL for the POST request.
    curl_easy_setopt(curl, CURLOPT_URL, post_url);

    // Explicitly set the HTTP method to POST.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    // Initialize the headers list and set the Content-Type header.
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Set the headers for the request.
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the POST data.
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    // Perform the POST request.
    res = curl_easy_perform(curl);

    // Check if the request was successful.
    if (res != CURLE_OK) {
      // Print error message if the request failed.
      fprintf(stderr, "POST request failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up the CURL session.
    curl_easy_cleanup(curl);
    // Free the headers list.
    curl_slist_free_all(headers);
  } else {
    // Print error message if CURL initialization failed.
    fprintf(stderr, "Failed to initialize curl handle\n");
  }
}

// Perform a GET request and print the response.
void get_all(const char *url) {
  // Initialize a CURL session handle.
  CURL *curl = curl_easy_init();

  if (curl) {
    CURLcode res;

    // Set the URL for the GET request.
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Perform the GET request.
    res = curl_easy_perform(curl);

    // Check if the request was successful.
    if (res != CURLE_OK) {
      // Print error message if the request failed.
      fprintf(stderr, "GET request failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up the CURL session.
    curl_easy_cleanup(curl);
  } else {
    // Print error message if CURL initialization failed.
    fprintf(stderr, "Failed to initialize curl handle\n");
  }
}

// Function to perform a GET request by ID and print the response.
void get_by_id(const char *url, const char *id) {
  // Initialize a CURL session handle.
  CURL *curl = curl_easy_init();

  if (curl) {
    CURLcode res;

    // Construct the URL for the GET request with the given ID.
    char get_by_id_url[URL_MAX_LENGTH];
    snprintf(get_by_id_url, sizeof(get_by_id_url), "%s%s/", url, id);

    // Set the URL for the GET request.
    curl_easy_setopt(curl, CURLOPT_URL, get_by_id_url);

    // Perform the GET request.
    res = curl_easy_perform(curl);

    // Check if the request was successful.
    if (res != CURLE_OK) {
      // Print error message if the request failed.
      fprintf(stderr, "GET request failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up the CURL session.
    curl_easy_cleanup(curl);
  } else {
    // Print error message if CURL initialization failed.
    fprintf(stderr, "Failed to initialize curl handle\n");
  }
}

// Function to perform an update request by ID.
void update(const char *url, const char *id, const char *data) {
  // Initialize a CURL session handle.
  CURL *curl = curl_easy_init();

  if (curl) {
    CURLcode res;
    char update_url[URL_MAX_LENGTH];
    // Concatenate the url with the other arguments.
    snprintf(update_url, sizeof(update_url), "%s%s%s/", url, "update/", id);

    // Set the URL for the PUT request.
    curl_easy_setopt(curl, CURLOPT_URL, update_url);

    // Explicitly set the HTTP method to PUT.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

    // Initialize the headers list and set the Content-Type header.
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Set the headers for the request.
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the PUT data.
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    // Perform the PUT request.
    res = curl_easy_perform(curl);

    // Check if the request was successful.
    if (res != CURLE_OK) {
      // Print error message if the request failed.
      fprintf(stderr, "PUT request failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up the CURL session.
    curl_easy_cleanup(curl);
    // Free the headers list.
    curl_slist_free_all(headers);
  } else {
    // Print error message if CURL initialization failed.
    fprintf(stderr, "Failed to initialize curl handle\n");
  }
}

// Function to perform a delete request
void delete(const char *url, const char *id) {
  // Initialize a CURL session handle.
  CURL *curl = curl_easy_init();

  if (curl) {
    CURLcode res;
    char delete_url[URL_MAX_LENGTH];
    // Concatenate the url with the other arguments.
    snprintf(delete_url, sizeof(delete_url), "%s%s%s/", url, "delete/", id);

    // Set the URL for the DELETE request.
    curl_easy_setopt(curl, CURLOPT_URL, delete_url);

    // Explicitly set the HTTP method to DELETE.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    // Perform the DELETE request.
    res = curl_easy_perform(curl);

    // Check if the request was successful.
    if (res != CURLE_OK) {
      // Print error message if the request failed.
      fprintf(stderr, "DELETE request failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up the CURL session.
    curl_easy_cleanup(curl);
  } else {
    // Print error message if CURL initialization failed.
    fprintf(stderr, "Failed to initialize curl handle\n");
  }
}

// Extract value from a line.
void extract_value(const char *line, char *value) {
  const char *delimiter = "=";
  char *copy = strdup(line);
  char *token = strtok(copy, delimiter);
  token = strtok(NULL, delimiter);

  if (token) {
    strcpy(value, token);
  }
  free(copy);
}

// Function to read the .env file and extract values
void read_env_file(
  const char *filename,
  char *url,
  char *post_payload,
  char *put_payload,
  char *id_get,
  char *id_update,
  char *id_delete
) {
  FILE *env = fopen(filename, "r");

  if (env == NULL) {
    fprintf(stderr, "Failed to open %s file\n", filename);
    exit(EXIT_FAILURE);
  }

  char line[LINE_MAX_LENGTH];

  while (fgets(line, sizeof(line), env) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strncmp(line, "URL=", 4) == 0) {
      extract_value(line, url);
    } else if (strncmp(line, "POST_PAYLOAD=", 13) == 0) {
      extract_value(line, post_payload);
    } else if (strncmp(line, "PUT_PAYLOAD=", 12) == 0) {
      extract_value(line, put_payload);
    } else if (strncmp(line, "ID_GET=", 7) == 0) {
      extract_value(line, id_get);
    } else if (strncmp(line, "ID_UPDATE=", 10) == 0) {
      extract_value(line, id_update);
    } else if (strncmp(line, "ID_DELETE=", 10) == 0) {
      extract_value(line, id_delete);
    }
  }

  fclose(env);
}

int main(void) {
  char post_payload[PAYLOAD_MAX_LENGTH];
  char put_payload[PAYLOAD_MAX_LENGTH];
  char url[URL_MAX_LENGTH];
  char id_get[ID_MAX_LENGTH];
  char id_update[ID_MAX_LENGTH];
  char id_delete[ID_MAX_LENGTH];

  read_env_file(
    ".env",
    url,
    post_payload,
    put_payload,
    id_get,
    id_update,
    id_delete
  );

  post(url, post_payload);
  get_all(url);
  get_by_id(url, id_get);
  update(url, id_update, put_payload);
  delete(url, id_delete);

  return 0;
}
