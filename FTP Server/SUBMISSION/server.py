import socket
import threading
import os

server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 23056
server.bind((IP_ADDR,port))
server.listen()

clients=[]
dict1={"abc":"123","xyz":"123"}
dict2={"abc":1,"xyz":1}
list1=["test1","test2"]

def listfiles(client):
    listing = [f for f in os.listdir("./files") ]
    if len(listing)!=0:
        mess="\n".join(listing)
        client.send(mess.encode())
    else:
        mess="NO FILES STORED CURRENTLY"
        client.send(mess.encode())

def stor(client,filename):

    filename1=filename
    image_size_bytes = client.recv(4)
    image_size = int.from_bytes(image_size_bytes, byteorder='big')
    image_data = b''
    while len(image_data) < image_size:
        chunk = client.recv(image_size - len(image_data))
        if not chunk:
            break
        image_data += chunk
    with open("./files/"+filename1, 'wb') as file:
        file.write(image_data)
    
    print('Received successfully the file:', filename) 
    return


def retr(client,filename):
    if os.path.isfile("./files/"+filename):
        try:
            client.send("EXISTS".encode())
            with open("./files/"+filename, 'rb') as file:
                image_data = file.read()
            
            client.sendall(len(image_data).to_bytes(4, byteorder='big'))
            client.sendall(image_data)
            os.remove("./files/"+filename)
            print("TRANSFER COMPLETED")
        except IOError:
            print("File not Found")
    else:
        client.send("NO".encode())







def client_options(usr, message,client):
    try:
        if(message=="1"):
            print(f"{usr}:requested LIST")
            listfiles(client)
            print(f"{usr}:Request COMPLETE")
        
        elif(message=="2"):
            print(f"{usr}:requested STORE")
            filename=client.recv(1024).decode()
            if(filename!="+++!!!NO!!!+++"):
                if os.path.isfile("./files/"+filename):
                    client.send("1".encode())
                else:
                    client.send("2".encode())
                    stor(client,filename)   
                    print(f"{usr}:Request COMPLETE")         
           
        elif(message=="3"):
            print(f"{usr}:requested RETR")
            name_file=client.recv(1024).decode()
            retr(client,name_file)
            print(f"{usr}:Request COMPLETE")
        
        
        elif(message=="4"):
            print(f"{usr}:QUITTED")
            client.close()
        # else:
        #     print("INVALID INPUT")
        #     client.close()

    except Exception as e:
        index = clients.index(client)
        clients.remove(client)
        
        client.close()





def client_path(usr,client):
  while True:
        try:
            # Receive a message from the client
            message = client.recv(1024).decode()
            # Broadcast the message to all other clients
            client_options(usr,message, client)
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
                    print(f"\nCONNECTED {usrname}:{address}")
                    clients.append(client)
                    if(dict2[key]==1):
                        client.send("UNBANNED".encode())
                        threading.Thread(target=client_path,args=(usrname,client)).start()
                    else:
                        client.send("BANNED".encode())
                else:
                    client.send("Incorrect Password".encode())
                    client.close()
        if(bool):
            client.send("NO".encode())
            client.close()
        
def admin_func():
    while True:
        print("---------ADMIN FUNCTIONS-----------")
        print("1.ADD USER\n2.DEL USER\n3.BAN\n4.UNBAN\n")
        choice=input("Please Enter your choice(1/2/3/4):")
        if(choice=="1"):
            usr_name=input("ENTER USERNAME TO BE ADDED:")
            pass_wd=input("ENTER PASSWORD OF NEW ACCOUNT:")
            dict1.update({usr_name:pass_wd})
            dict2.update({usr_name:1})
            print("SUCCESFULLY ADDED")
        if(choice=="2"):
            usr_name=input("ENTER USERNAME TO BE DELETED:")
            if(usr_name in dict1.keys()):
                del dict1[usr_name]
                del dict2[usr_name]
                print("SUCCESSFULLY DELETED")
            else:
                print("USER-NAME NOT THERE")
        if(choice=="3"):
            usr_name=input("ENTER USERNAME TO BE BANNED:")
            if(usr_name in dict2.keys()):
                if(dict2[usr_name]!=0):
                    dict2[usr_name]=0
                    print("SUCCESSFULLY BANNED")
                else:
                    print("ALREADY BANNED")
            else:
                print("USER-NAME NOT THERE")
        if(choice=="4"):
            usr_name=input("ENTER USERNAME TO BE UNBANNED:")
            if(usr_name in dict2.keys()):
                if(dict2[usr_name]!=1):
                    dict2[usr_name]=1
                    print("SUCCESSFULLY UNBANNED")
                else:
                    print("ALREADY UNBANNED")
            else:
                print("USER-NAME NOT THERE")


if __name__=="__main__":

    user_name=input("ENTER ADMIN USERNAME:")
    pass_word=input("ENTER ADMIN PASSWORD:")
    #ADMIN USERNAME AND PASSWORD CHANGE
    if(user_name=="nis" and pass_word=="123"):
        print("WELCOME ADMIN")
        threading.Thread(target=accept_client).start()
        threading.Thread(target=admin_func).start()


    