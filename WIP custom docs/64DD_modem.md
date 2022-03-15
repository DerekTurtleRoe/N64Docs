# 64DD modem

64DD Log: Modem works?
So, in the past few days, I’ve been working on making use of the modem that came with the Randnet Starter Kit. I got a working Randnet Disk and partially working Mario Artist Communication Kit, I got at least two disks I can mess with when it’s about accessing the web. Things got a little complicated however.

Here was the original plan that I had in mind when I started doing this:
I wanted to use a Raspberry Pi as the means to go from Dialup to WiFi. Thanks to DreamPi, most of the work was already done. This was one of the ways to play Dreamcast games online, and since it uses Dialup this is a really good base to work with.

But this is not enough to work with Randnet, and for that, let’s have a breakdown of how this should go:

1. Dialup
First of all, as you connect, you need to dial the number. That was how ISPs worked back then, meaning that Randnet is pretty much the 64DD ISP. So it dials the number (selectable by region in Randnet), and then if it answers the call, starts sending PPP packets, the first step to Internet.

In this case, before anything happens, each side (Modem and ISP) wants to know how the other talks with what conditions and what not. Both has to acknowledge by responding back. This is the easy part.

2. CHAP Authentication
Now my ISP from the Raspberry Pi side tries to assign an IP to the N64 Modem. And then N64 cuts the connection, implying I did an authentication error. Makes sense, it wants to authenticate. But I’m a networking illiterate, and this took ages to find out.

PPP has two authentication protocols: PAP and CHAP. One is totally not secure because the password is sent plaintext, the other is more secure and relies on a secret that both sides knows but never sends that directly. PPPD on Linux knows how to deal with both, so I tried with PAP and it was not happy. I tried with CHAP and it tried to respond. This was what it wanted, now the thing that matters is finding a way for the authentication to be accepted.

You can actually bypass this using a RADIUS server apparently but this is so hard to use that I went back on finding the secret password instead, and I found one: “K1QU0K@N”. For some reason however, this only works with Mario Artist Communication Kit. Fine, because that one actually gives feedback of what is going on on screen. You can set pppd to ignore the username on the other side and voila, authentication is done.

3. IPCP Assignment
Assigning IPs depends on how you set pppd, and this part goes well without any problems after authentication has succeeded.

4. Connect to www.randnet.ne.jp?
So now it’s all about the domain and connecting somewhere. The domain was recently registered by jrra, someone familiar with 64DD hardware and software, so the DNS should actually respond, right? Nope.

This was one of the hardest part. You see, on Randnet, you cannot setup the connection unlike Dreamcast allows you to do, or pretty much anything that has a modem and a service that doesn’t rely on a unique ISP.

Well it sends DNS requests but it doesn’t answer back, implying that the request was not actually listened to. The DNS server IP is 172.16.10.30. I was let known that this is within the private IPs, just like 192.168.*.* IPs. So it won’t go anywhere, this IP is private, so I have to setup a DNS server on my Raspberry Pi instead.

I installed dnsmasq, and manually set up www.randnet.ne.jp in the hosts file, and also did something maybe weird with the IPs to make sure it can respond.

I’ve set up the N64 IP to be 192.168.*.*, so within the local network, while the Raspberry Pi is 172.16.10.30, at least to the N64 only. My DNS server answers with an IP. And then from this point on, it does succeed to connect outside.

5. GetCommunicationConfig ???
Well now that’s currently the problem. You see, the first thing it wants to load is this URL, through the HTTP/1.0 protocol:

http://www.randnet.ne.jp/servlet/GetCommunicationConfig

It is only responded with error 404. And I kind of stopped there. Knowing what it wants requires reverse enginnering, and I’ll be honest: I don’t quite like the N64 for that.

That’s it for this log for now. The next one will be about setting it up yourself, if you want to continue what I started.