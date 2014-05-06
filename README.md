led_matrix
==========

Raspberry Pi で、秋月の K-03735 を動かすプロジェクト

## setup

install wiringpi

- http://wiringpi.com/download-and-install/

and...

    $ sudo apt-get install dh-autoreconf
    $ sudo gem install bundler
    $ bundle install --path vendor/bundle
    $ (cd ext; bundle exec ruby extconf.rb; make clean; make)

## test

    $ bundle exec rspec spec/**/*_spec.rb -fn -c
