#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>
#include <string>
#include "testlib.h"

#define MAX_FILE_NAME_LENG 1024
#define MAX_DOUBLE_LEN 1024

#define EPS (1e-6)

bool relative_equal(double true_value, double x) {
    if(true_value == 0) return fabs(x) <= EPS;
    return fabs((true_value - x) / true_value) <= EPS;
}

bool validate_double(std::string s) {

    if(s.empty())
        return false;

    int st = 0;
    if(s[0] == '-')
        st++;

    if(!isdigit(s[st]))
        return false;

    bool point = false;

    for(int i=st; i<s.size(); i++) {
        if(s[i] == '.') {
            if(point)
                return false;
            else
                point = true;
        }
        else {
            if(!isdigit(s[i]))
                return false;
        }
    }

    if(s.back() == '.')
        return false;

    return true;
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        fprintf(stdout, "insufficient number of command line args\n");
        return 1;
    }

    char sInFile[MAX_FILE_NAME_LENG];
    char sDiffFile[MAX_FILE_NAME_LENG];
    char sOutFile[MAX_FILE_NAME_LENG];

    FILE *fpDiff = fopen(argv[4], "r");
    if (!fpDiff) {
        fprintf(stdout, "failed to open diff %s\n", argv[4]);
        return 1;
    }

    FILE *fpOut = fopen(argv[6], "r");
    if (!fpOut) {
        fprintf(stdout, "failed to open out %s\n", argv[6]);
        fclose(fpDiff);
        return 1;
    }

    char diff_cs[MAX_DOUBLE_LEN];
    fscanf(fpDiff, "%s", diff_cs);
    fclose(fpDiff);

    char out_cs[MAX_DOUBLE_LEN];
    fscanf(fpOut, "%s", out_cs);
    fclose(fpOut);

    if(strcmp(diff_cs, out_cs) == 0) {
      return 0;
    }

    std::string diff_str = diff_cs;
    std::string out_str = out_cs;

    if(!validate_double(diff_str)) {
      ensuref(false, "judge validation failed. judge value is not double.");
    }

    if(!validate_double(out_str)) {
      return 1;
    }

    double true_value = stod(diff_str);
    double out_value = stod(out_str);

    if(fabs( true_value - out_value ) <= EPS || relative_equal(true_value, out_value)) {
        return 0;
    }
    
    return 1;
}
