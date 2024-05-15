import socket
import threading
import os

server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 23056
server.bind((IP_ADDR,port))
server.listen()

clients=[]
dict1={"abc":"123","abd":"123"}
list1=["test","test2"]

def listfiles(client):
    listing = [f for f in os.listdir("./files") ]
    if len(listing)!=0:
        mess="\n".join(listing)
        client.send(mess.encode())
    else:
        mess="NO FILES STORED CURRENTLY"
        client.send(mess.encode())

def stor(client,filename):
    list1.append(filename)
    data = client.recv(1024).decode() 


    filename1 = filename
    with open("./files/"+filename1, 'w') as fileadd:
        fileadd.write(data) 

    print('Received successfully the file:', filename) 
    return

def retr(client,filename):
    if os.path.isfile("./files/"+filename):
        try:
            client.send("EXISTS".encode())
            with open("./files/"+filename,'r') as file:
                print("TRANSFER INITIATE")
                data=file.read()
                client.send(str(data).encode())
            os.remove("./files/"+filename)
            print("TRANSFER COMPLETED")
        except IOError:
            print("File not Found")
    else:
        client.send("NO".encode())







def client_options(message,client):
    try:
        if(message=="1"):
            print("LIST")
            listfiles(client)
        
        elif(message=="2"):
            print("STORE")
            filename=client.recv(1024).decode()
            if os.path.isfile("./files/"+filename):
                client.send("1".encode())
            else:
                client.send("2".encode())
                stor(client,filename)
            
           
        elif(message=="3"):
            print("RETR")
            name_file=client.recv(1024).decode()
            retr(client,name_file)
        
        
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
    server.close()