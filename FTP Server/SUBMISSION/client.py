import socket
import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 23056
username=input("Please Enter your USERNAME:")
password=input("Please Enter your PASSWORD:")

client.connect((IP_ADDR,port))
message = client.recv(1024).decode()



if message == "USERNAME":
    client.send(username.encode())
    m1=client.recv(1024).decode()
    if(m1=="PASSWORD"):
        client.send(password.encode())
        m2=client.recv(1024).decode()
        if(m2=="CONNECTED"):
            while(True):
                print("Choose your OPERATION:\n1.LIST\n2.STORE\n3.RETR\n4.QUIT")
                sendm=input("Please choose(1/2/3/4):")
                client.send(sendm.encode())
                if sendm not in ["1","2","3"]:
                    break

                




# # Function to send messages to the server
# def send_message():
#     while True:
#         try:
#             message = input()  # Take input from the user
#             client.send(f"{nick} : {message}".encode())  # Send the message to the server along with the nickname
            
#         except:
#             print("An error occurred!")
#             client.close()
#             break

# # Function to receive messages from the server
# def receive_message():
#     while True:
#         try:
#             messages = client.recv(1024)  # Receive messages from the server
#             print(messages.decode())  # Print the received messages
#         except:
#             print("An error occurred!")
#             client.close()
#             break

# receive_thread = threading.Thread(target=send_message)
# send_thread = threading.Thread(target=receive_message)

# receive_thread.start()
# send_thread.start()
