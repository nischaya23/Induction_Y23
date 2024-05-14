import socket
import threading
import os

server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 23056
server.bind((IP_ADDR,port))
server.listen()

clients=[]
dict1={"abc":"123"}
list1=[]

def stor(filename):
    return

def retr(filename):
    return

def client_options(message,client):
    try:
        if(message=="1"):
            print("LIST")
            
        elif(message=="2"):
            print("STORE")
           
        elif(message=="3"):
            print("RETR")
            
        elif(message=="4"):
            print("QUIT")
            client.close()
        else:
            print("INVALID INPUT")
            client.close()

    except Exception as e:
        index = clients.index(client)
        clients.remove(client)
        
        client.close()





def client_path(client):
  while True:
        try:
            # Receive a message from the client
            message = client.recv(1024).decode()
            # Broadcast the message to all other clients
            client_options(message, client)
        except:
            # If an error occurs, remove the client and their nickname, then close the connection
            index = clients.index(client)
            clients.remove(client)
            client.close()
            break



def accept_client():
    while True:
        # Accept a new client connection
        client, address = server.accept()
        print(f"\nConnection received from {address}")

        # Ask the client for their nickname
        client.send("USERNAME".encode())
        usrname = client.recv(1024).decode()

        bool=True
        for key,value in dict1.items():
            if(key==usrname):
                bool=False
                client.send("PASSWORD".encode())
                password=client.recv(1024).decode()
                if(password==value):
                    client.send("CONNECTED".encode())
                    clients.append(client)
                    threading.Thread(target=client_path,args=(client,)).start()
                else:
                    client.send("Incorrect Password".encode())
                    client.close()
        if(bool):
            client.send("NO".encode())
            client.close()
        

if __name__=="__main__":
    accept_client()
