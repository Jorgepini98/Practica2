# Practica2
En esta práctica tiene como objetivo el uso de RTOS en el ESP32 y diseñar un firmware basado en RTOS.
1.	Se han creado dos tareas en la que una enciende y apaga un LED, y otra que envia “Hola mundo” via UART. 
2.	Mediante comunicación I2C se ha definido una tarea que lee la aceleración cada 100ms y otra que manda los datos leídos en sincronía con el parpadeo del LED.
3.	Se habilita el modo de bajo consumo (iddleHook)
