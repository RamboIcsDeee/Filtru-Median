#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Imagine
{
    string tip;
    int width = 0;
    int height = 0;
    int maxi = 0;
    vector<vector<int>> pixels;

    void print(string out)
    {
        ofstream fout(out);
        fout << tip << endl;
        fout << width << " " << height << endl;
        fout << maxi << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fout << pixels[i][j] << " ";
            }
            fout << endl;
        }
    }
};
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
int bubbleSort(vector<int> arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return arr[arr.size() / 2];
}
void Merge(vector<int>& A, int p, int q, int r)
{
    const int n1 = q - p + 1;
    int i, j, k;
    const int n2 = r - q;
    int left[50];
    int right[50];

    for (i = 0; i < n1; i++)
    {
        left[i] = A[p + i];
    }
    for (j = 0; j < n2; j++)
    {
        right[j] = A[q + j + 1];
    }

    i = 0;
    j = 0;

    for (k = p; i < n1 && j < n2; k++)
    {
        if (left[i] < right[j])
        {
            A[k] = left[i++];
        }
        else
        {
            A[k] = right[j++];
        }
    }

    while (i < n1)
    {
        A[k++] = left[i++];
    }

    while (j < n2)
    {
        A[k++] = right[j++];
    }
}
void MergeSort(vector<int>& A, int p, int r)
{
    int q;

    if (p < r)
    {
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}
int verificare_pixel(struct Imagine& img, int dimensiune, int linie, int coloana, string optiune)
{
    vector<int> window;
    for (int windowRow = linie - dimensiune / 2; windowRow <= linie + dimensiune / 2; windowRow++)
    {
        for (int windowCol = coloana - dimensiune / 2; windowCol <= coloana + dimensiune / 2; windowCol++)
        {
            int numar;
            int x, y;
            x = windowRow;
            y = windowCol;
            if (windowRow < 0)
            {
                x = 0;
            }
            if (windowRow >= img.height)
            {
                x = img.height - 1;
            }
            if (windowCol < 0)
            {
                y = 0;
            }
            if (windowCol >= img.width)
            {
                y = img.width - 1;
            }
            numar = img.pixels[x][y];
            window.push_back(numar);
        }
    }
    if (optiune == "bubble")
    {
        return bubbleSort(window, window.size());
    }
    else
    {
        MergeSort(window, 0, window.size() - 1);
        return window[window.size() / 2];
    }

}
void citire(struct Imagine& img, string in)
{
    vector<string> lines;
    vector<string> args;
    ifstream fin(in);
    int c = 0;
    string buffer;
    while (c < 3)
    {
        getline(fin, buffer);
        if (buffer[0] == '#')
        {

        }
        else
        {
            lines.push_back(buffer);
            c++;
        }
    }
    for (int i = 1; i < 3; i++)
    {
        lines[0] = lines[0] + ' ' + lines[i];
    }
    string temp = lines[0];
    istringstream iss(temp);
    iss >> img.tip >> img.width >> img.height >> img.maxi;
    for (int i = 0; i < img.height; i++)
    {
        vector<int> linie;
        for (int j = 0; j < img.width; j++)
        {
            int pixel;
            fin >> pixel;
            linie.push_back((int)pixel);
        }
        img.pixels.push_back(linie);
    }
}

int main() {
    string optiune;
    int dim_fer;
    struct Imagine* imag = new struct Imagine;
    struct Imagine* imag_noua = new struct Imagine;
    string input_file;
    string output_file;
    cin >> optiune >> dim_fer >> input_file >> output_file;
    citire(*imag, input_file);
    int max = 0;
    int pix;
    for (int i = 0; i < imag->height; i++)
    {
        vector<int> linie;
        for (int j = 0; j < imag->width; j++)
        {
            pix = verificare_pixel(*imag, dim_fer, i, j, optiune);
            linie.push_back(pix);
            if (max < pix)
            {
                max = pix;
            }
        }
        imag_noua->pixels.push_back(linie);
    }
    imag_noua->tip = imag->tip;
    imag_noua->width = imag->width;
    imag_noua->maxi = max;
    imag_noua->height = imag->height;
    imag_noua->print(output_file);
    free(imag);
    return 0;
}
