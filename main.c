#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

COORD coord= {0,0};

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

struct Products
{
    char productName[50];
    int Price;
    int Quantity;
};
typedef struct Products Products;
struct Category
{
    char categoryName[50];
    Products *prod;
    int ProductsCount;
};
typedef struct Category Category;

struct SkinCareStore
{
    Category *cat;
    int categoryCount;
};
typedef struct SkinCareStore SkinCareStore;

void initialize(SkinCareStore *skinCare)
{
    skinCare->categoryCount=3;
    skinCare->cat = malloc(100 * sizeof(Category));

    for (int i = 0; i < 3; i++)
    {
        skinCare->cat[i].prod = malloc(3 * sizeof(Products));
        skinCare->cat[i].ProductsCount = 2;
    }


    strcpy(skinCare->cat[0].categoryName,"FacialCleansers");
    strcpy(skinCare->cat[1].categoryName,"FacialMoisturizers");
    strcpy(skinCare->cat[2].categoryName,"EyeCare");

    strcpy(skinCare->cat[0].prod[0].productName,"Starvile");
    strcpy(skinCare->cat[0].prod[1].productName,"Eva");
    strcpy(skinCare->cat[1].prod[0].productName,"Cerave");
    strcpy(skinCare->cat[1].prod[1].productName,"LaRochePosay");
    strcpy(skinCare->cat[2].prod[0].productName,"Eucerin");
    strcpy(skinCare->cat[2].prod[1].productName,"Beesline");

    skinCare->cat[0].prod[0].Price=200;
    skinCare->cat[0].prod[1].Price=400;
    skinCare->cat[1].prod[0].Price=300;
    skinCare->cat[1].prod[1].Price=700;
    skinCare->cat[2].prod[0].Price=800;
    skinCare->cat[2].prod[1].Price=1000;

    skinCare->cat[0].prod[0].Quantity=10;
    skinCare->cat[0].prod[1].Quantity=10;
    skinCare->cat[1].prod[0].Quantity=10;
    skinCare->cat[1].prod[1].Quantity=10;
    skinCare->cat[2].prod[0].Quantity=10;
    skinCare->cat[2].prod[1].Quantity=10;

}
void Display(SkinCareStore *skinCare)
{
    for(int i=0; i<skinCare->categoryCount; i++)
    {
        printf("Category %d : %s \n",i+1,skinCare->cat[i].categoryName);
        printf("Products in this category :\n");
        for(int j=0; j<skinCare->cat[i].ProductsCount; j++)
        {
            printf("      %d - Product name:  %s || Product price: %d || Product quantity: %d \n",j+1,skinCare->cat[i].prod[j].productName,skinCare->cat[i].prod[j].Price,skinCare->cat[i].prod[j].Quantity);

        }
    }
}


void AddCategory(SkinCareStore *skinCare)
{
    if(skinCare->categoryCount<100)
    {
        printf("Please enter category name :");
        scanf("%s",skinCare->cat[skinCare->categoryCount].categoryName);
        skinCare->cat[skinCare->categoryCount].prod = malloc(3 * sizeof(Products));
        skinCare->cat[skinCare->categoryCount].ProductsCount=0;
        skinCare->categoryCount++;
        printf("Category added successfully\n");
    }
    else
    {
        printf("Sorry there is no space :");
    }
}


void AddProduct(SkinCareStore* skinCare)
{
    char catName[50], prodName[50];
    int price, quantity;
    int catIndex = -1;
    int prodIndex = -1;

    for (int i = 0; i < skinCare->categoryCount; i++)
    {
        printf("%d - %s\n", i + 1, skinCare->cat[i].categoryName);
    }

    printf("Please choose the category of the product and write its name:\n");
    scanf("%s", catName);

    for (int i = 0; i < skinCare->categoryCount; i++)
    {
        if (strcmp(skinCare->cat[i].categoryName, catName) == 0)
        {
            catIndex = i;
            break;
        }
    }

    if (catIndex != -1)
    {
        if (skinCare->cat[catIndex].ProductsCount < 3)
        {
            printf("Please enter the product name:\n");
            scanf("%s", prodName);

            for (int i = 0; i < skinCare->cat[catIndex].ProductsCount; i++)
            {
                int result = strcmp(skinCare->cat[catIndex].prod[i].productName, prodName);
                if (result == 0)
                {
                    prodIndex = i;
                    break;
                }
            }

            if (prodIndex != -1)
            {
                printf("This product already exists.\n");
                printf("Do you want to edit it? (Y/N): ");
                char YesOrNo;
                scanf(" %c", &YesOrNo);

                if (YesOrNo == 'Y')
                {
                    printf("Enter the new price:\n");
                    scanf("%d", &price);
                    skinCare->cat[catIndex].prod[prodIndex].Price = price;
                    printf("Enter the new quantity:\n");
                    scanf("%d", &quantity);
                    skinCare->cat[catIndex].prod[prodIndex].Quantity += quantity;
                    printf("Updated Successfully.\n");
                }
                else
                {
                    printf("Thanks.\n");
                }
            }
            else
            {
                printf("Enter the price:\n");
                scanf("%d", &price);
                printf("Enter the quantity:\n");
                scanf("%d", &quantity);
                strcpy(skinCare->cat[catIndex].prod[skinCare->cat[catIndex].ProductsCount].productName, prodName);
                skinCare->cat[catIndex].prod[skinCare->cat[catIndex].ProductsCount].Price = price;
                skinCare->cat[catIndex].prod[skinCare->cat[catIndex].ProductsCount].Quantity = quantity;
                skinCare->cat[catIndex].ProductsCount++;
                printf("Product added successfully.\n");
            }
        }
        else
        {
            Products* newProd= malloc((skinCare->cat[catIndex].ProductsCount + 1) * sizeof(Products));
            for (int i = 0; i < skinCare->cat[catIndex].ProductsCount; i++)
            {
                newProd[i] = skinCare->cat[catIndex].prod[i];
            }
            free(skinCare->cat[catIndex].prod);
            skinCare->cat[catIndex].prod = newProd;

            printf("Please enter the product name:\n");
            scanf("%s", prodName);

            for (int i = 0; i < skinCare->cat[catIndex].ProductsCount; i++)
            {
                int result = strcmp(skinCare->cat[catIndex].prod[i].productName, prodName);
                if (result == 0)
                {
                    prodIndex = i;
                    break;
                }
            }

            if (prodIndex != -1)
            {
                printf("This product already exists.\n");
                printf("Do you want to edit it? (Y/N): ");
                char YesOrNo;
                scanf(" %c", &YesOrNo);

                if (YesOrNo == 'Y')
                {
                    printf("Enter the new price:\n");
                    scanf("%d", &price);
                    skinCare->cat[catIndex].prod[prodIndex].Price = price;
                    printf("Enter the new quantity:\n");
                    scanf("%d", &quantity);
                    skinCare->cat[catIndex].prod[prodIndex].Quantity += quantity;
                    printf("Updated Successfully.\n");
                }
                else
                {
                    printf("Thanks.\n");
                }
            }
            else
            {
                printf("Enter the price:\n");
                scanf("%d", &price);
                printf("Enter the quantity:\n");
                scanf("%d", &quantity);
                strcpy(skinCare->cat[catIndex].prod[skinCare->cat[catIndex].ProductsCount].productName, prodName);
                skinCare->cat[catIndex].prod[skinCare->cat[catIndex].ProductsCount].Price = price;
                skinCare->cat[catIndex].prod[skinCare->cat[catIndex].ProductsCount].Quantity = quantity;
                skinCare->cat[catIndex].ProductsCount++;
                printf("Product added successfully.\n");
            }
        }
    }
    else
    {
        printf("Category not found.\n");
    }
}

void freeMemory(SkinCareStore* skinCare)
{
    for (int i = 0; i < skinCare->categoryCount; i++)
    {
        free(skinCare->cat[i].prod);
    }
    free(skinCare->cat);
}

void RemoveCategory(SkinCareStore *skinCare)
{
    printf("Which category do you want to delete?\n");
    char Name [50];
    scanf("%s",Name);
    int index=-1;
    if(skinCare->categoryCount>0)
    {

        for(int i=0; i<skinCare->categoryCount; i++)
        {
            if(strcmp(skinCare->cat[i].categoryName,Name)==0)
            {
                index=i;
                break;

            }
        }
        if(index!=-1)
        {
            for(int i=index; i<skinCare->categoryCount-1; i++)
            {
                skinCare->cat[i]=skinCare->cat[i+1];
            }
            skinCare->categoryCount--;
            printf("Category removed successfully \n");

        }
        else
        {
            printf("Category not found\n");
        }
    }
    else
    {
        printf("There are no categories\n");
    }


}

void RemoveProduct(SkinCareStore *skinCare)
{
    char catName[50],prodName[50];
    int catIndex,prodIndex=-1;
    printf("Enter product name you want to remove \n");
    scanf("%s",prodName);
    printf("Enter category name that you want to remove product from it \n");
    scanf("%s",catName);
    for(int i=0; i<skinCare->categoryCount; i++)
    {
        if(strcmp(skinCare->cat[i].categoryName,catName)==0)
        {
            catIndex=i;
            break;

        }
    }
    if(catIndex!=-1)
    {
        for(int i=0; i<skinCare->cat[catIndex].ProductsCount; i++)
        {
            if(strcmp(skinCare->cat[catIndex].prod[i].productName,prodName)==0)
            {
                prodIndex=i;
                break;
            }
        }
        if(prodIndex!=-1)
        {
            for(int i=prodIndex; i<skinCare->cat[catIndex].ProductsCount-1; i++)
            {
                skinCare->cat[catIndex].prod[i]=skinCare->cat[catIndex].prod[i+1];
            }
            skinCare->cat[catIndex].ProductsCount--;
            printf("Product removed successfully \n");

        }
        else
        {
            printf("This product not found in this category");
        }
    }
    else
    {
        printf("Category not found \n");
    }



}
void SellProduct(SkinCareStore *skinCare)
{
    char catName[50],prodName[50];
    int catIndex,prodIndex=-1;
    printf("Enter product name you want to sell \n");
    scanf("%s",prodName);
    printf("Enter category name that you want to sell product from it \n");
    scanf("%s",catName);
    for(int i=0; i<skinCare->categoryCount; i++)
    {
        if(strcmp(skinCare->cat[i].categoryName,catName)==0)
        {
            catIndex=i;
            break;

        }
    }
    if(catIndex!=-1)
    {
        for(int i=0; i<skinCare->cat[catIndex].ProductsCount; i++)
        {
            if(strcmp(skinCare->cat[catIndex].prod[i].productName,prodName)==0)
            {
                prodIndex=i;
                break;
            }
        }
        if(prodIndex!=-1)
        {
            int quantityToSell;
            printf("Enter quantity you need to sell \n");
            scanf("%d",&quantityToSell);
            if(quantityToSell<skinCare->cat[catIndex].prod[prodIndex].Quantity)
            {
                skinCare->cat[catIndex].prod[prodIndex].Quantity -=quantityToSell;
                printf("Done \n");
            }
            else
            {
                printf("Sorry , There are this quantity ( %d ) only for this product\n",skinCare->cat[catIndex].prod[prodIndex].Quantity);
            }

        }
        else
        {
            printf("This product not found in this category");
        }
    }
    else
    {
        printf("Category not found \n");
    }


}

void MoveProduct(SkinCareStore *skinCare)
{
    char prodName[50], fromCatName[50], toCatName[50];
    int fromCatIndex = -1, toCatIndex = -1, prodIndex = -1;

    printf("Enter category you want to move product from it\n");
    scanf("%s", fromCatName);

    for (int i = 0; i < skinCare->categoryCount; i++)
    {
        if (strcmp(skinCare->cat[i].categoryName, fromCatName) == 0)
        {
            fromCatIndex = i;
            break;
        }
    }

    if (fromCatIndex != -1)
    {
        printf("Enter product name you want to move\n");
        scanf("%s", prodName);

        for (int i = 0; i < skinCare->cat[fromCatIndex].ProductsCount; i++)
        {
            if (strcmp(skinCare->cat[fromCatIndex].prod[i].productName, prodName) == 0)
            {
                prodIndex = i;
                break;
            }
        }
    }
    else
    {
        printf("This category not found\n");
    }

    if (prodIndex != -1)
    {
        printf("Enter category name you want to move to it\n");
        scanf("%s", toCatName);

        for (int i = 0; i < skinCare->categoryCount; i++)
        {
            if (strcmp(skinCare->cat[i].categoryName, toCatName) == 0)
            {
                toCatIndex = i;
                break;
            }
        }
    }
    else
    {
        printf("This product not found\n");
    }

    if (toCatIndex != -1)
    {
        if (skinCare->cat[toCatIndex].ProductsCount < 100)
        {
            skinCare->cat[toCatIndex].prod[skinCare->cat[toCatIndex].ProductsCount] = skinCare->cat[fromCatIndex].prod[prodIndex];
            skinCare->cat[toCatIndex].ProductsCount++;

            for (int i = prodIndex; i < skinCare->cat[fromCatIndex].ProductsCount - 1; i++)
            {
                skinCare->cat[fromCatIndex].prod[i] = skinCare->cat[fromCatIndex].prod[i + 1];
            }
            skinCare->cat[fromCatIndex].ProductsCount--;

            printf("Product moved successfully\n");
        }
        else
        {
            printf("Destination category is full\n");
        }
    }
    else
    {
        printf("Destination category not found\n");
    }
}



int main()
{
    SkinCareStore skin;
    SkinCareStore *s=&skin;
    initialize(s);

    int selection =0;
    while(1)
    {

        system("cls");
        gotoxy(40,7);
        if(selection==0)
        {
            SetColor(13);
            printf("***Display skincare store***");
            SetColor(15);
        }
        else
        {

            printf("   Display skincare store   ");
        }
        gotoxy(40,9);
        if(selection==1)
        {
            SetColor(13);
            printf("***Add category***");
            SetColor(15);
        }
        else
        {

            printf("   Add category   ");
        }
        gotoxy(40,10);
        if(selection==2)
        {
            SetColor(13);
            printf("***Add product***");
            SetColor(15);
        }
        else
        {

            printf("   Add product   ");
        }
        gotoxy(40,12);
        if(selection==3)
        {
            SetColor(13);
            printf("***Remove category***");
            SetColor(15);

        }
        else
        {

            printf("   Remove category   ");
        }
        gotoxy(40,13);
        if(selection==4)
        {
            SetColor(13);
            printf("***Remove product***");
            SetColor(15);

        }
        else
        {

            printf("   Remove product   ");
        }
        gotoxy(40,15);
        if(selection==5)
        {
            SetColor(13);
            printf("***Move product from category to another***");
            SetColor(15);

        }
        else
        {

            printf("   Move product from category to another   ");
        }
        gotoxy(40,16);
        if(selection==6)
        {
            SetColor(13);
            printf("***Sell products***");
            SetColor(15);

        }
        else
        {

            printf("   Sell products   ");
        }
        gotoxy(40,18);
        if(selection==7)
        {
            SetColor(13);
            printf("***Exit***");
            SetColor(15);

        }
        else
        {

            printf("   Exit   ");
        }





        char key;
        key=_getch();
        switch(key)
        {
        //  _getch();

        case 72:
            if(selection<=0)
            {
                selection=7;
            }
            else
            {
                selection--;
            }
            break;
        case 80:
            if(selection>=7)
            {
                selection=0;
            }
            else
            {
                selection++;
            }
            break;


        case 13:
            switch(selection)
            {
            case 0:
                system("cls");
                Display(s);
                _getch();
                break;
            case 1:
                system("cls");
                AddCategory(s);
                _getch();
                break;
            case 2:
                system("cls");
                AddProduct(s);
                _getch();
                break;
            case 3:
                system("cls");
                RemoveCategory(s);
                _getch();
                break;
            case 4:
                system("cls");
                RemoveProduct(s);
                _getch();
                break;
            case 5:
                system("cls");
                MoveProduct(s);
                _getch();
                break;
            case 6:
                system("cls");
                SellProduct(s);
                _getch();
                break;
            case 7:
                system("cls");
                return 0;
                break;

            }

        }

    }

    freeMemory(s);
    return 0;
}
