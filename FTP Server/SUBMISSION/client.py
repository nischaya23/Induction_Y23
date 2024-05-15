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
                    print("Sending File")
                    with open(m1, 'rb') as file:
                        # Read the image data
                        image_data = file.read()
                    # Send the image size first
                    client.sendall(len(image_data).to_bytes(4, byteorder='big'))
                    # Send the image data
                    client.sendall(image_data)
                    os.remove(m1)
                    print("File Sent")
                except IOError:
                    print("Entered invalid filename!!\nPlease re-enter filename.")
        else:
            print("FILE doesn't exist")
            client.send("+++!!!NO!!!+++".encode())#COUNTER NAME TO TELL SERVER TO NOT EXECUTE ANY COMMAND



    if(sendm=="3"):
        m2=input("Please enter name of file you want to retrieve:")
        client.send(m2.encode())
        y=client.recv(1024).decode()
        if(y=="EXISTS"):
            try: 
                print("Started Accepting.....")
                filename1=m2
                image_size_bytes = client.recv(4)
                image_size = int.from_bytes(image_size_bytes, byteorder='big')
                image_data = b''
                while len(image_data) < image_size:
                    chunk = client.recv(image_size - len(image_data))
                    if not chunk:
                        break
                    image_data += chunk
                with open(filename1, 'wb') as file:
                    file.write(image_data)
                print("File Accepted")
                return
            except IOError:
                print("InputOutput ERROR")
        
        else:
            print("File Doesn't Exist")




if message == "USERNAME":
    client.send(username.encode())
    m1=client.recv(1024).decode()
    if(m1=="PASSWORD"):
        client.send(password.encode())
        m2=client.recv(1024).decode()
        if(m2=="CONNECTED"):
            m3=client.recv(1024).decode()
            if(m3=="UNBANNED"):
                print("SUCCESSFULLY Connected")
                while(True):
                    # print("Type of")
                    
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
            elif(m3=="BANNED"):
                print("Your account is banned")
        else:
            print("Wrong USERNAME or PASSWORD")
