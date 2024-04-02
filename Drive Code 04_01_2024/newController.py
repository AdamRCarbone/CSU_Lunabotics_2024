import pygame
import socket
pygame.init()


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
UDP_IP = "192.168.0.101"
UDP_PORT = 3000 


def remap(x):
   x = int((-49*x)+50)
   if x < 10:
       return "0" + str(x)
   if 45 <= x & 55 >= x:
       return "50"
   return str(x)
    



# This is a simple class that will help us print to the screen.
# It has nothing to do with the joysticks, just outputting the
# information.

def main():
    # Set the width and height of the screen (width, height), and name the window.

    oldMessage = ""
    # Used to manage how fast the screen updates.
    clock = pygame.time.Clock()


    # Get ready to print.

    # This dict can be left as-is, since pygame will generate a
    # pygame.JOYDEVICEADDED event for every joystick connected
    # at the start of the program.
    joysticks = {}

    done = False
    while not done:
        # Event processing step.
        # Possible joystick events: JOYAXISMOTION, JOYBALLMOTION, JOYBUTTONDOWN,
        # JOYBUTTONUP, JOYHATMOTION, JOYDEVICEADDED, JOYDEVICEREMOVED
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True  # Flag that we are done so we exit this loop.

            if event.type == pygame.JOYBUTTONDOWN:
               # print("Joystick button pressed.")
                if event.button == 0:
                    joystick = joysticks[event.instance_id]

            if event.type == pygame.JOYBUTTONUP:
               #print("Joystick button released.")
                pass

            # Handle hotplugging
            if event.type == pygame.JOYDEVICEADDED:
                # This event will be generated when the program starts for every
                # joystick, filling up the list without needing to create them manually.
                joy = pygame.joystick.Joystick(event.device_index)
                joysticks[joy.get_instance_id()] = joy
                print(f"Joystick {joy.get_instance_id()} connencted")

            if event.type == pygame.JOYDEVICEREMOVED:
                del joysticks[event.instance_id]
                print(f"Joystick {event.instance_id} disconnected")

        # Drawing step
        # First, clear the screen to white. Don't put other drawing commands
        # above this, or they will be erased with this command.
       # Limit to 30 frames per second.
        for joystick in joysticks.values():
            MESSAGE =  remap(joystick.get_axis(1))+ remap(joystick.get_axis(3)) + str(joystick.get_hat(0)[1]+1) + str(joystick.get_button(0))
            if MESSAGE != oldMessage:
                print(MESSAGE)
                sock.sendto(bytes(MESSAGE, "utf-8"), (UDP_IP, UDP_PORT))
                oldMessage = MESSAGE




        clock.tick(5)



if __name__ == "__main__":
    main()
    # If you forget this line, the :program will 'hang'
    # on exit if running from IDLE.
    pygame.quit()
