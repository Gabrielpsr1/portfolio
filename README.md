this is like a log of the process of coding this CNN

1- In my first try, I used one hidden layer and the follow parameters:
    filters = 32
    dropout = 0.5
    hidden_layer_units = 128
    pool_sz = 2, 2
    kernel_size = 3, 3
the result was kinda bad:
333/333 - 2s - 5ms/step - accuracy: 0.0551 - loss: 3.5058
I'll try to apply more filters, increase the number of hidden layers and not modify the pool_size or the kernell

2- added one layer, and the parameters are:
    filters = 48
    dropout = 0.5
    hidden_layer_units = 256
    pool_sz = 2, 2
    kernel_size = 3, 3
the result still pretty bad:
333/333 - 2s - 5ms/step - accuracy: 0.0536 - loss: 3.5067
no progress
try to add more convolutional layers, and since doubling the units in a hidden layer didn't took me any futher, i'll go back to just 128

3- Went back to 128 units, added two more convolutional layers, each one doubling the filter the last had to compensate the pooling.
so the filters are something like: 32->64->128
and after the filters and pool sizing there are 3 hidden layers with 128 units
dropout, pool_sz and kernel_size are all the same as before
results are way better now:
333/333 - 2s - 7ms/step - accuracy: 0.6202 - loss: 1.0348
maybe adding one more conv layer and one more hidden layer can make it even better, since every layer I'm doubling the number of filters

4- for this model, I've increase the number of conv layers from 3 to 4 and the same for for hidden layers. I've decided to double the number of units for each layer
great results:
333/333 - 3s - 8ms/step - accuracy: 0.8513 - loss: 0.4270
thinking about appling more filters, since adding more conv layers is virtually impossible because the pool size have gone till the limit and adding one more hidden layer, so the program can classify the data more accurately

5 - I've add one more hidden layer and add more filters to the last conv layer. Didn't work at all
333/333 - 2s - 7ms/step - accuracy: 0.3850 - loss: 1.7613
i'll go back to 4's configs and add one more hidden layer

6- 333/333 - 2s - 7ms/step - accuracy: 0.5956 - loss: 1.1588

7- 333/333 - 4s - 13ms/step - accuracy: 0.3857 - loss: 1.8663

after many attempts turns outn that 4's configs where the best, and lowering the dropout to 0.4 I could get:
333/333 - 3s - 8ms/step - accuracy: 0.9267 - loss: 0.2678