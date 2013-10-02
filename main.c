#include "similarity_calculator.h"
#include <stdio.h>

char* read_file_content();

int main(int argc, const char * argv[]) {
  char* sequence = read_file_content(
      "/Users/Sam/CppPrograms/HPC_project_c_version_sequential/HIV-1_db.fasta.txt");
  char* polymerase = read_file_content(
      "/Users/Sam/CppPrograms/HPC_project_c_version_sequential/HIV_polymerase.fasta.txt");

  initialize(polymerase, sequence);
  calculate_similarity();
  pretty_print();
	return 0;
}

char* read_file_content(char* file_path) {
  long f_size;
  char* content;
  size_t code_s;
  FILE* fp = fopen(file_path, "r");
  fseek(fp, 0, SEEK_END);
  f_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  code_s = sizeof(char) * f_size;
  content = malloc(code_s);
  fread(content, 1, f_size, fp);

  return content;
}
