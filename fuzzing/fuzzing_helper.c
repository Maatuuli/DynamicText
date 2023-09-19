/*
The MIT License (MIT)
Copyright (c) 2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

void
setUpRandomFilledText(char** text, int32_t sizeInBytes)
{
    (*text) = customMalloc(sizeInBytes * sizeof(char));

    customMemset((*text), '\0', sizeInBytes);

    for (int32_t index = 0; index < (sizeInBytes - 1); index++)
    {
        (*text)[index] = rand() % 256;
    }
}
