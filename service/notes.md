/etc/systemd/system


/etc/udev/rules.d
sudo udevadm control --reload-rules && sudo udevadm trigger
systemctl list-units --type=device --all | grep tinythinker

journalctl -u polarone