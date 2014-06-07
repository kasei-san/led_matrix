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

## 動作確認

    $ sudo ruby -e "require './lib/led_intermediator.rb'; ctr = LedIntermediator.instance.set_str('test'); sleep(30)"
