# Communication between the control board & the connectivity module
In our case, the control board is the `Nucleo-Board (stm32f446re)` where as
the connectivity module is `esp32 dev board`.

## brief
I will send the data of the users from the connectivity module to the 
control board via `UART` and I will move the data from UART DR to the 
memory by using `DMA` to reduce the overload from the CPU.

### User Profile
It's 1st version of the user profile and we may updata it later.
```
typedef struct __attribute__((__packed__))
{
    int user_id;
    char user_name[20];

    unsigned int speed_limit;

    Door_Access door;
    Engine_Access engine;
    Trunk_Access trunk;

} userData;

typedef enum __attribute__((__packed__))
{
  Door_Off,
  Door_On
}Door_Access;

typedef enum __attribute__((__packed__))
{
  Engine_Off,
  Engine_On
}Engine_Access;

typedef enum __attribute__((__packed__))
{
  Trunk_Off,
  Trunk_On
}Trunk_Access;
```
size of user profile is `31 Byte`

## Nucleo-Board
I will use `USART1` on Nucleo-Board.

USART1:

	- connected on which bus --> APB2
	- connected to which DMA --> DMA2
	- connected to which channel --> channel 4
	- connected to which stream --> stream 2
 
USART1 Pins:

	- Tx pin --> PA9
	- Rx pin --> PA10

## Esp32 board
I will use `UART2` on esp32 board.

UART2 Pins:

	- Tx pin --> GPIO16
	- Rx pin --> GPIO17
	
## Connection between Nucleo-board and Esp32

### Hardware Connection
    --------------------                                ---------------
    |   Nucleo-board   |                                |    Esp32    |
    |               Tx |<------------------------------>| Rx          |
    |               Rx |<------------------------------>| Tx          |
    |              GND |<------------------------------>| GND         |
    --------------------                                ---------------
    
### Logic Levels of Nucleo-board
```
ViL				0.8 volt
ViH				2.0 volt
VoL				0.4 volt
VoH				2.4 volt
```

### Logic Levels of Esp32
```
ViL				0.25 VDD = 0.825 volt
ViH				0.75 VDD = 2.475 volt
VoL				0.10 VDD = 0.330 volt
VoH				0.80 VDD = 2.640 volt
```

### Mapping logic levels

        3.3V --------------- ===========================> -------------- 3.3V
             |   logic 1   |         high signal          |   logic 1  |
       2.64V --------------- ===========================> |            |
                                                          -------------- 2V
                                                       

                                                         -------------- 0.8V
    0.33V --------------- =============================> |   logic 0   |
          |   logic 0   |         low signal             |             |
       0V --------------- =============================> --------------- 0V
      
from the figure, we will not need to the level shifter
      
## Test the communication
we will send the data of three users from esp32 to nucleo-borad
### esp32
In this image we will find the data of each user:
![gitHub](https://github.com/eslam276/Graduation_Project/blob/Control_Board/Code/imgs/users_data_on_esp32.JPG)

### nucleo-board
In these images, we receive correctly the data of each user from the esp32
![gitHub](https://github.com/eslam276/Graduation_Project/blob/Control_Board/Code/imgs/user1.JPG)
![gitHub](https://github.com/eslam276/Graduation_Project/blob/Control_Board/Code/imgs/user2.JPG)
![gitHub](https://github.com/eslam276/Graduation_Project/blob/Control_Board/Code/imgs/user3.JPG)

### Photo Hardware Connections
![gitHub](https://github.com/eslam276/Graduation_Project/blob/Control_Board/Code/imgs/Hardware_Connection.JPG)

### Video of Testing Communication with Hardware
[Hardware Testing](https://drive.google.com/file/d/1IxUkaF-9Y51Cl0l2jt8NhuUZwfqpblEt/view?usp=drive_link)
[Recieve Date From Firebase via ESP32](https://drive.google.com/file/d/1f52qGiq6aSy2GIB3K1Zr7QCJu4A69BkA/view?usp=drive_link)
