import socket
import threading
import os

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 23056
username=input("Please Enter your USERNAME:")
password=input("Please Enter your PASSWORD:")

client.connect((IP_ADDR,port))
message = client.recv(1024).decode()


def client_handle(client,sendm):
    if(sendm=="1"):
        mess=client.recv(1024).decode()
        print(mess)
    if(sendm=="2"):
        m1=input("Please enter name of file you want to send:")
        if(os.path.isfile(m1)):
            client.send(m1.encode())
            x=client.recv(1024).decode()
            if(x=="1"):
                print("File already Exists")
                return
            else:
                try:
                    with open(m1,'r') as File:
                        print("Sending File")
                        data = File.read() 
                        client.send(str(data).encode()) 
                    os.remove(m1) 
                    print("File Sent")
                except IOError:
                    print("Entered invalid filename!!\nPlease re-enter filename.")
        else:
            print("FILE doesn't exist")
    if(sendm=="3"):
        m2=input("Please enter name of file you want to retrieve:")
        client.send(m2.encode())
        y=client.recv(1024).decode()
        if(y=="EXISTS"):
            try: 
                print("Started Accepting.....")
                data=client.recv(1024).decode()
                filename1=m2
                with open(filename1,'w') as file:
                    file.write(data)
                print("File Accepted")
            except IOError:
                print("File Already EXISTS with you")
        
        else:
            print("File Doesn't Exist")




if message == "USERNAME":
    client.send(username.encode())
    m1=client.recv(1024).decode()
    if(m1=="PASSWORD"):
        client.send(password.encode())
        m2=client.recv(1024).decode()
        if(m2=="CONNECTED"):
            print("SUCCESSFULLY Connected")
            while(True):
                print("Choose your OPERATION:\n1.LIST\n2.STORE\n3.RETR\n4.QUIT")
                sendm=input("Please choose(1/2/3/4):")
                if sendm not in ["1","2","3","4"]:
                    client.send(sendm.encode())
                    print("INVALID INPUT")
                    break
                elif sendm in ["4"]:
                    client.send(sendm.encode())
                    print("QUITTING.....")
                    break
                else:
                    client.send(sendm.encode())
                    client_handle(client,sendm)

