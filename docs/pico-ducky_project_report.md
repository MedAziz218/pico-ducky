[GitHub Project](https://github.com/MedAziz218/pico-ducky):https://github.com/MedAziz218/pico-ducky
## 1- Reverse Shell 
•A reverse shell is a type of shell session in which a remote computer can control another computer's shell session.
•The attacker's software, called a “payload”, connects to a listener on the victim's machine, granting the attacker shell access. This enables the attacker to execute commands, access files, and manipulate the file system remotely.
#### Advantages of reverse shell
• It bypasses firewall restrictions as it often uses common outbound ports.
•It's harder to detect as it appears as normal outgoing traffic.
•It doesn't require the victim's machine to be directly accessible from the internet, unlike SSH or other remote access methods.
#### Drawbacks of reverse shell
- harder to setup on the victim machine
## 2- EVIL MAID
•An evil maid attack Targets an unattended devices
•It refers to any cyber attack that requires physical access to the victim.
•The term "Evil Maid" is often used as a general concept to describe a category of attacks where an attacker gains physical access to a device when it's unattended and tampers with it.

## 3- BAD USB
•***BadUSB*** attack exploits the inherent vulnerability in USB that allows USB devices to be reprogrammed to act as human interface devices, enabling them to execute malicious commands on connected computers undetected.
•A **malicious** USB device, **disguised** as a legitimate peripheral, is used to exploit vulnerabilities in a target system.
•The bad USB device acts as an innocent HID device such as (keyboard, mouse, flash drive …) **but** it discreetly executes commands or runs malicious programs on the victim's computer.

Examples of BAD USBs: 
- Rubber Ducky: a famous device created specifically to be used as a bad usb
- flipper zero: a versatile hacking tool that can also act as a bad usb
- ***pico-ducky***: this is our project, our own version of rubber ducky

## 4- Our attack: the *pico-ducky*

Pico-ducky is our own iteration of "rubber-ducky". it is based on a "raspberrypi pico w". it acts as a USB keyboard . it is capable of executing command (payloads) on the victim machine in very short time.
when plugged in it runs a script that starts a reverse shell on the victim machine giving us full access to it.

### a. how we made it
- **Hardware:**  
The pico ducky is based on a "raspberryPi Pico W*" a powerful microcontroller created by the famous *Raspberry Pi foundation*
we chose the picoW specifically due to its capability to act as a **programmable** **usb HID device** 

- **Software:**
There are many ways to program the picoW, the most common way being the micro python framework, but after thorough testing we found this method yields very slow results. 
C++ was the more suitable choice for our purposes due to it s significant speed and customizability.
 for comparison here is the time took to inject a payload of 259 charecters with both frameworks
> **Micro Python: 5 seconds**
> **Arduino/C++: 2 seconds**

## b. additional tools used
the bad usb device on it s own can do significant things like executing commands on the victim machine, but to make a more powerful attack, specifically a  **reverse shell*** it needed to be coupled with some additional tools:

- **CHIMERA Reverse Shell script:** this is a script that, as the name says, is used to create reverse shells. It is made by talented people and contains many techniques and hacks that make it able to bypass windows security, firewalls and malware detection softwares.
- **AZURE VM:** we made use of a cloud virtual machine to make the hack accessible at all time and not depend on our attacker machine to be on all the time. Also the static ip of the cloud machine made it easier for us and we did not need to change the payload of the pico-ducky at all.

### c. overview of the attack
here is a step by step description of the attack:
1. Gain physical access to the victim machine
2. plug in the pico ducky 
3. wait for the pico ducky to inject its payload (less than 2 seconds)
4. remove the pico ducky and get away
> at this point the attack is basically done as the rest of the steps will be done automatically

5. the victim machine will download and execute the CHIMERA script, which will create a reverse shell between it and our AZURE Cloud VM
6. at this point all we need to do is ssh into our cloud VM and use it to access the victim machine

### 5- Difficulties Faced
•Problem: Attacker machine has Variable IP address -> require changing the payload every time
•Solution: Using Azure VM because it has static IP and is always on
•Solution: Making it easy to change the payload

•Problem: wrong keyboard layout (QWERTY or AZERTY) can ruin the attack because the  pico-ducky can’t detect it
•Solution: adding a way to select the right layout on the pico-ducky

## 6- Testing and Validation
•while making the pico-ducky code we used harmless payloads to test it , for example a payload that changes the wallpaper, and another that opens the calculator

•We used virtual machines to test the final attack

